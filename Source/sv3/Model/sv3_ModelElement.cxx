#include "sv3_ModelElement.h"

#include "sv_OCCTSolidModel.h"
#include "sv_PolyDataSolid.h"
#include "sv_polydatasolid_utils.h"

#include <vtkCleanPolyData.h>

using sv3::ModelElement;

ModelElement::ModelElement()
    : m_Type(), m_InnerSolid(nullptr), m_WholeVtkPolyData(nullptr), m_MaxDist(20.0),
      m_NumSampling(0), m_UseUniform(0)
{
}

ModelElement::~ModelElement()
{
    delete m_InnerSolid;
}

std::vector<std::string> ModelElement::GetFaceNames() const
{
    std::vector<std::string> names;
    for (auto const& face : m_Faces) {
        names.push_back(face.name);
    }
    return names;
}

std::vector<int> ModelElement::GetWallFaceIDs() const
{
    std::vector<int> ids;
    for (auto const& face : m_Faces) {
        if (face.type == "wall") {
            ids.push_back(face.id);
        }
    }
    return ids;
}

std::map<std::string,int> ModelElement::GetFaceNameIDMap() const
{
    std::map<std::string,int> nameIDMap;
    for (auto const& face : m_Faces) {
        nameIDMap[face.name] = face.id;
    }
    return nameIDMap;
}

std::string ModelElement::GetFaceName(int id) const
{
    for (auto const& face : m_Faces) {
        if (face.id == id) {
            return face.name;
        }
    }
    return "";
}

int ModelElement::GetFaceID(const std::string& name) const
{
    for (auto const& face : m_Faces) {
        if (face.name == name) {
            return face.id;
        }
    }
    return -1;
}

int ModelElement::GetFaceIDFromInnerSolid(const std::string& faceName) const
{
    if (m_InnerSolid == nullptr) {
        return -1;
    }

    int numFaces = 0;
    int* ids = nullptr;
    if (m_InnerSolid->GetFaceIds(&numFaces, &ids) != SV_OK) {
        return -1;
    }

    for (int i = 0; i < numFaces; i++) {
        char* value = nullptr;
        m_InnerSolid->GetFaceAttribute("gdscName", ids[i], &value);
        if (value != nullptr && faceName == std::string(value)) {
            return ids[i];
        }
    }

    return -1;
}

std::vector<std::string> ModelElement::GetFileExtensions() const
{
    if (m_Type == "PolyData") {
        return {"vtp", "vtk", "vtu", "stl", "ply"};
    } else if (m_Type == "OpenCASCADE") {
        return {"brep", "step", "iges", "stl"};
    } else if (m_Type == "Parasolid") {
        return {"xmt_txt"};
    }
    return {};
}

//------------------------
// CreateSolidModelForType
//------------------------
// Construct a fresh, empty cvSolidModel for the given kernel type name.
//
// Mirrors the kernel constructor map in _PythonAPI/Modeling_PyModule.cxx
// (CvSolidModelCtorMap); duplicated locally rather than shared since this
// sv3 library sits below _PythonAPI and can't depend on it.
//
static cvSolidModel*
CreateSolidModelForType(const std::string& type)
{
  if (type == "OpenCASCADE") {
      return new cvOCCTSolidModel();
  } else if (type == "PolyData") {
      return new cvPolyDataSolid();
  }
  return nullptr;
}

bool ModelElement::ReadFile(const std::string& filePath)
{
    if (m_Type == "PolyData") {
        auto pd = vtkSmartPointer<vtkPolyData>::New();
        if (PlyDtaUtils_ReadNative(const_cast<char*>(filePath.c_str()), pd) != SV_OK) {
            return false;
        }

        auto cleaner = vtkSmartPointer<vtkCleanPolyData>::New();
        cleaner->SetInputData(pd);
        cleaner->Update();

        vtkSmartPointer<vtkPolyData> cleanpd = cleaner->GetOutput();
        cleanpd->BuildLinks();

        m_WholeVtkPolyData = cleanpd;
        return true;
    }

    m_InnerSolid = CreateSolidModelForType(m_Type);
    if (m_InnerSolid == nullptr) {
        return false;
    }

    return m_InnerSolid->ReadNative(const_cast<char*>(filePath.c_str())) == SV_OK;
}

bool ModelElement::WriteFile(const std::string& filePath)
{
    if (m_Type == "PolyData") {
        if (!m_WholeVtkPolyData) {
            return true;
        }
        return PlyDtaUtils_WriteNative(m_WholeVtkPolyData, 0, const_cast<char*>(filePath.c_str())) == SV_OK;
    }

    if (m_InnerSolid == nullptr) {
        // No solid to write is not an error (matches sv4guiModelElementOCCT::WriteFile).
        return true;
    }

    return m_InnerSolid->WriteNative(0, const_cast<char*>(filePath.c_str())) == SV_OK;
}

vtkSmartPointer<vtkPolyData> ModelElement::CreateFaceVtkPolyData(int id) const
{
    if (m_Type == "PolyData") {
        if (!m_WholeVtkPolyData) {
            return nullptr;
        }
        auto facepd = vtkPolyData::New();
        PlyDtaUtils_GetFacePolyData(m_WholeVtkPolyData.GetPointer(), &id, facepd);
        return vtkSmartPointer<vtkPolyData>::Take(facepd);
    }

    if (m_InnerSolid == nullptr) {
        return nullptr;
    }

    auto facePolyData = m_InnerSolid->GetFacePolyData(id, 1, m_MaxDist);
    if (facePolyData == nullptr) {
        return nullptr;
    }
    return facePolyData->GetVtkPolyData();
}

vtkSmartPointer<vtkPolyData> ModelElement::CreateWholeVtkPolyData() const
{
    if (m_Type == "PolyData") {
        return m_WholeVtkPolyData;
    }

    if (m_InnerSolid == nullptr) {
        return nullptr;
    }

    auto wholePolyData = m_InnerSolid->GetPolyData(1, m_MaxDist);
    if (wholePolyData == nullptr) {
        return nullptr;
    }
    return wholePolyData->GetVtkPolyData();
}
