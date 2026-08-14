// sv3_MeshGroup.h
//
// Lightweight, MITK-free replacement for sv4guiMitkMesh.
// Stores a time-varying series of meshes as meshGroup[time].
//
#ifndef SV3_MESHGROUP_H
#define SV3_MESHGROUP_H

#include <memory>
#include <string>
#include <vector>

#include "sv3_Mesh.h"

#include <vtkSV3MeshModule.h>

namespace sv3 {

class VTKSV3MESH_EXPORT MeshGroup {
public:
    MeshGroup();

    MeshGroup(const MeshGroup&) = delete;
    MeshGroup& operator=(const MeshGroup&) = delete;
    MeshGroup(MeshGroup&&) = default;
    MeshGroup& operator=(MeshGroup&&) = default;

    std::string GetType() const { return m_Type; }
    void SetType(const std::string& type) { m_Type = type; }

    std::string GetModelName() const { return m_ModelName; }
    void SetModelName(const std::string& name) { m_ModelName = name; }

    unsigned int GetTimeSize() const { return m_Meshes.size(); }
    void Expand(unsigned int timeSteps);

    Mesh* GetMesh(unsigned int t = 0) const;
    void SetMesh(std::unique_ptr<Mesh> mesh, unsigned int t = 0);

    static std::unique_ptr<MeshGroup> CreateGroupFromFile(const std::string& fileName,
        bool readSurfaceMesh, bool readVolumeMesh);
    static void WriteToFile(const MeshGroup* group, const std::string& fileName);

private:
    std::string m_Type;
    std::string m_ModelName;
    std::vector<std::unique_ptr<Mesh>> m_Meshes;
};

} // namespace sv3

#endif // SV3_MESHGROUP_H
