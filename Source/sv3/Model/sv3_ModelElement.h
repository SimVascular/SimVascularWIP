// sv3_ModelElement.h
//
// Lightweight, MITK-free replacement for sv4guiModelElement /
// sv4guiModelElementPolyData / sv4guiModelElementOCCT.
//
// Unlike the sv4gui class hierarchy (a base class plus a PolyData/Analytic/OCCT
// subclass for each kernel), this is a single concrete class that dispatches on
// GetType() ("PolyData" or "OpenCASCADE", matching SolidModel_KernelT_StrToEnum()
// in sv_SolidModel.cxx) since both kernels the Python API supports read/write
// through APIs that are already kernel-polymorphic (cvSolidModel::ReadNative()/
// WriteNative(), or the PlyDtaUtils_* functions for the PolyData kernel, which
// has no cvSolidModel of its own).
//
#ifndef SV3_MODELELEMENT_H
#define SV3_MODELELEMENT_H

#include <map>
#include <string>
#include <vector>

#include "sv_SolidModel.h"

// For svLoftingParam, itself already a lightweight, MITK-free struct.
#include "sv3_ContourGroup.h"

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <vtkSV3ModelModule.h>

namespace sv3 {

class VTKSV3MODEL_EXPORT ModelElement {
public:

    // Mirrors sv4guiModelElement::svFace, minus the GUI-only cached face
    // vtkPolyData (never serialized, so not needed for file fidelity).
    struct ModelFace {
        int id = 0;
        std::string name;
        std::string type;
        bool visible = true;
        float opacity = 1.0f;
        float color[3] = {1.0f, 1.0f, 1.0f};
    };

    // Mirrors sv4guiModelElement::svBlendParamRadius.
    struct BlendParamRadius {
        int faceID1 = 0;
        int faceID2 = 0;
        double radius = 0.0;
        std::string faceName1;
        std::string faceName2;
    };

    // Mirrors sv4guiModelElement::svBlendParam.
    struct BlendParam {
        int numblenditers = 2;
        int numsubblenditers = 3;
        int numsubdivisioniters = 1;
        int numcgsmoothiters = 2;
        int numlapsmoothiters = 50;
        double targetdecimation = 0.01;
    };

    ModelElement();
    ~ModelElement();

    std::string GetType() const { return m_Type; }
    void SetType(const std::string& type) { m_Type = type; }

    cvSolidModel* GetInnerSolid() const { return m_InnerSolid; }
    void SetInnerSolid(cvSolidModel* solid) { m_InnerSolid = solid; }

    vtkSmartPointer<vtkPolyData> GetWholeVtkPolyData() const { return m_WholeVtkPolyData; }
    void SetWholeVtkPolyData(vtkSmartPointer<vtkPolyData> pd) { m_WholeVtkPolyData = pd; }

    // Tessellation resolution used for OCCT/Parasolid face/whole polydata creation.
    double GetMaxDist() const { return m_MaxDist; }
    void SetMaxDist(double maxDist) { m_MaxDist = maxDist; }

    int GetNumSampling() const { return m_NumSampling; }
    void SetNumSampling(int numSampling) { m_NumSampling = numSampling; }

    int IfUseUniform() const { return m_UseUniform; }
    void SetUseUniform(int useUniform) { m_UseUniform = useUniform; }

    svLoftingParam* GetLoftingParam() { return &m_LoftingParam; }

    std::vector<std::string> GetSegNames() const { return m_SegNames; }
    void SetSegNames(const std::vector<std::string>& segNames) { m_SegNames = segNames; }

    std::vector<ModelFace> GetFaces() const { return m_Faces; }
    void SetFaces(const std::vector<ModelFace>& faces) { m_Faces = faces; }
    std::vector<std::string> GetFaceNames() const;

    std::vector<BlendParamRadius> GetBlendRadii() const { return m_BlendRadii; }
    void SetBlendRadii(const std::vector<BlendParamRadius>& blendRadii) { m_BlendRadii = blendRadii; }

    BlendParam* GetBlendParam() { return &m_BlendParam; }

    std::vector<int> GetWallFaceIDs() const;
    std::map<std::string,int> GetFaceNameIDMap() const;

    // Look up a face's name/ID from the currently-set faces (SetFaces()),
    // not from the underlying solid model.
    std::string GetFaceName(int id) const;
    int GetFaceID(const std::string& name) const;

    // Find a face's ID by name via the underlying solid model's own face
    // attributes ("gdscName"), independent of what's in GetFaces(). Used to
    // re-sync face IDs after loading a solid whose kernel renumbers faces
    // between save and load (e.g. Parasolid).
    int GetFaceIDFromInnerSolid(const std::string& faceName) const;

    // Native file extensions for this element's kernel, most-preferred first.
    std::vector<std::string> GetFileExtensions() const;

    bool ReadFile(const std::string& filePath);
    bool WriteFile(const std::string& filePath);

    vtkSmartPointer<vtkPolyData> CreateFaceVtkPolyData(int id) const;
    vtkSmartPointer<vtkPolyData> CreateWholeVtkPolyData() const;

private:
    std::string m_Type;
    cvSolidModel* m_InnerSolid;
    vtkSmartPointer<vtkPolyData> m_WholeVtkPolyData;
    double m_MaxDist;
    int m_NumSampling;
    int m_UseUniform;
    svLoftingParam m_LoftingParam;
    std::vector<std::string> m_SegNames;
    std::vector<ModelFace> m_Faces;
    std::vector<BlendParamRadius> m_BlendRadii;
    BlendParam m_BlendParam;
};

} // namespace sv3

#endif // SV3_MODELELEMENT_H
