// sv3_Mesh.h
//
// Lightweight, MITK-free replacement for sv4guiMesh / sv4guiMeshTetGen.
//
// The sv4gui subclass (sv4guiMeshTetGen) doesn't override any of the base
// class's I/O methods -- it only sets a type name in its constructor -- so
// there's no need for a class hierarchy here, a single concrete class is
// enough.
//
#ifndef SV3_MESH_H
#define SV3_MESH_H

#include <string>
#include <vector>

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

#include <vtkSV3MeshModule.h>

namespace sv3 {

class VTKSV3MESH_EXPORT Mesh {
public:
    Mesh();

    std::string GetType() const { return m_Type; }
    void SetType(const std::string& type) { m_Type = type; }

    std::vector<std::string> GetCommandHistory() const { return m_CommandHistory; }
    void SetCommandHistory(const std::vector<std::string>& history) { m_CommandHistory = history; }

    vtkSmartPointer<vtkPolyData> GetSurfaceMesh() const { return m_SurfaceMesh; }
    void SetSurfaceMesh(vtkSmartPointer<vtkPolyData> surfaceMesh) { m_SurfaceMesh = surfaceMesh; }

    vtkSmartPointer<vtkUnstructuredGrid> GetVolumeMesh() const { return m_VolumeMesh; }
    void SetVolumeMesh(vtkSmartPointer<vtkUnstructuredGrid> volumeMesh) { m_VolumeMesh = volumeMesh; }

    bool ReadSurfaceFile(const std::string& filePath);
    bool ReadVolumeFile(const std::string& filePath);
    bool WriteSurfaceFile(const std::string& filePath) const;
    bool WriteVolumeFile(const std::string& filePath) const;

private:
    std::string m_Type;
    vtkSmartPointer<vtkPolyData> m_SurfaceMesh;
    vtkSmartPointer<vtkUnstructuredGrid> m_VolumeMesh;
    std::vector<std::string> m_CommandHistory;
};

} // namespace sv3

#endif // SV3_MESH_H
