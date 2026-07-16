#include "sv3_Mesh.h"

#include <fstream>
#include <iostream>

#include <vtkErrorCode.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridWriter.h>

using sv3::Mesh;

Mesh::Mesh()
    : m_Type(), m_SurfaceMesh(nullptr), m_VolumeMesh(nullptr)
{
}

//----------------
// ReadSurfaceFile
//----------------
// Ported from sv4guiMesh::ReadSurfaceFile()/CreateSurfaceMeshFromFile()
// (Source/sv4gui/Modules/_Mesh/_Common/sv4gui_Mesh.cxx).
//
bool Mesh::ReadSurfaceFile(const std::string& filePath)
{
    std::ifstream surfaceFile(filePath);
    if (!surfaceFile) {
        m_SurfaceMesh = nullptr;
        return true;
    }

    auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(filePath.c_str());
    reader->Update();
    m_SurfaceMesh = reader->GetOutput();

    return true;
}

//---------------
// ReadVolumeFile
//---------------
// Ported from sv4guiMesh::ReadVolumeFile()/CreateVolumeMeshFromFile().
//
bool Mesh::ReadVolumeFile(const std::string& filePath)
{
    std::ifstream volumeFile(filePath);
    if (!volumeFile) {
        m_VolumeMesh = nullptr;
        return true;
    }

    auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName(filePath.c_str());
    reader->Update();
    m_VolumeMesh = reader->GetOutput();

    return true;
}

//-----------------
// WriteSurfaceFile
//-----------------
// Ported from sv4guiMesh::WriteSurfaceFile().
//
bool Mesh::WriteSurfaceFile(const std::string& filePath) const
{
    if (!m_SurfaceMesh) {
        return true;
    }

    auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName(filePath.c_str());
    writer->SetInputData(m_SurfaceMesh);
    if (writer->Write() == 0 || writer->GetErrorCode() != 0) {
        std::cerr << "vtkXMLPolyDataWriter error: " << vtkErrorCode::GetStringFromErrorCode(writer->GetErrorCode()) << std::endl;
        return false;
    }

    return true;
}

//----------------
// WriteVolumeFile
//----------------
// Ported from sv4guiMesh::WriteVolumeFile().
//
bool Mesh::WriteVolumeFile(const std::string& filePath) const
{
    if (!m_VolumeMesh) {
        return true;
    }

    auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName(filePath.c_str());
    writer->SetInputData(m_VolumeMesh);
    if (writer->Write() == 0 || writer->GetErrorCode() != 0) {
        std::cerr << "vtkXMLUnstructuredGridWriter error: " << vtkErrorCode::GetStringFromErrorCode(writer->GetErrorCode()) << std::endl;
        return false;
    }

    return true;
}
