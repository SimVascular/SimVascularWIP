#include "sv3_MeshGroup.h"

#include <tinyxml2.h>

#include <iostream>
#include <stdexcept>

using sv3::MeshGroup;
using sv3::Mesh;

MeshGroup::MeshGroup()
    : m_Type(), m_ModelName(), m_Meshes(1)
{
    // A freshly-constructed group starts with one (empty) timestep, matching
    // sv4guiMitkMesh::InitializeEmpty(), called from its default constructor.
}

void MeshGroup::Expand(unsigned int timeSteps)
{
    if (timeSteps > m_Meshes.size()) {
        m_Meshes.resize(timeSteps);
    }
}

Mesh* MeshGroup::GetMesh(unsigned int t) const
{
    if (t < m_Meshes.size()) {
        return m_Meshes[t].get();
    }
    return nullptr;
}

void MeshGroup::SetMesh(std::unique_ptr<Mesh> mesh, unsigned int t)
{
    Expand(t + 1);
    m_Meshes[t] = std::move(mesh);
}

//---------------------------
// set_string_from_attribute
//---------------------------
// Get a string attribute from an XMLElement object.
//
static void set_string_from_attribute(
    tinyxml2::XMLElement *element, const char *attr_name, std::string &value) {
  const char *qvalue = "";
  element->QueryStringAttribute(attr_name, &qvalue);
  value = std::string(qvalue);
}

//---------------------
// CreateGroupFromFile
//---------------------
// Create a MeshGroup from a .msh file.
//
// Ported from sv4guiMitkMeshIO::ReadFromFile()
// (Source/sv4gui/Modules/_Mesh/_Common/sv4gui_MitkMeshIO.cxx) to remove
// _PythonAPI's dependency on sv4gui/MITK, reading the same XML schema so
// files remain interchangeable with the sv4gui GUI.
//
// Unlike sv4guiModelIO, the original of this function reports errors by
// logging and returning null rather than throwing -- preserved here since
// _PythonAPI/MeshingSeries_PyClass.cxx's caller checks for both a thrown
// exception and a null return.
//
std::unique_ptr<MeshGroup> MeshGroup::CreateGroupFromFile(const std::string& fileName,
    bool readSurfaceMesh, bool readVolumeMesh)
{
    tinyxml2::XMLDocument document;

    if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Could not open/read/parse " << fileName << std::endl;
        return nullptr;
    }

    auto mmElement = document.FirstChildElement("mitk_mesh");
    if (!mmElement) {
        std::cerr << "No Mesh data in " << fileName << std::endl;
        return nullptr;
    }

    auto group = std::make_unique<MeshGroup>();
    std::string meshType, modelName;
    set_string_from_attribute(mmElement, "type", meshType);
    set_string_from_attribute(mmElement, "model_name", modelName);
    group->SetType(meshType);
    group->SetModelName(modelName);

    int timestep = -1;

    for (auto timestepElement = mmElement->FirstChildElement("timestep");
         timestepElement != nullptr;
         timestepElement = timestepElement->NextSiblingElement("timestep")) {
        timestep++;
        group->Expand(timestep + 1);

        auto meshElement = timestepElement->FirstChildElement("mesh");
        if (meshElement == nullptr) {
            continue;
        }

        std::string type;
        set_string_from_attribute(meshElement, "type", type);

        auto mesh = std::make_unique<Mesh>();
        mesh->SetType(type);

        auto chElement = meshElement->FirstChildElement("command_history");
        if (chElement != nullptr) {
            std::vector<std::string> cmdHistory;
            for (auto cmdElement = chElement->FirstChildElement("command");
                 cmdElement != nullptr;
                 cmdElement = cmdElement->NextSiblingElement("command")) {
                std::string cmd;
                set_string_from_attribute(cmdElement, "content", cmd);
                cmdHistory.push_back(cmd);
            }
            mesh->SetCommandHistory(cmdHistory);
        }

        if (readSurfaceMesh) {
            std::string surfaceFileName = fileName.substr(0, fileName.find_last_of(".")) + ".vtp";
            mesh->ReadSurfaceFile(surfaceFileName);
        }

        if (readVolumeMesh) {
            std::string volumeFileName = fileName.substr(0, fileName.find_last_of(".")) + ".vtu";
            mesh->ReadVolumeFile(volumeFileName);
        }

        group->SetMesh(std::move(mesh), timestep);
    }

    return group;
}

//------------
// WriteToFile
//------------
// Write a MeshGroup to a .msh file.
//
// Ported from sv4guiMitkMeshIO::WriteGroupToFile()
// (Source/sv4gui/Modules/_Mesh/_Common/sv4gui_MitkMeshIO.cxx).
//
void MeshGroup::WriteToFile(const MeshGroup* group, const std::string& fileName)
{
    tinyxml2::XMLDocument document;
    auto decl = document.NewDeclaration();
    document.LinkEndChild(decl);

    auto mmElement = document.NewElement("mitk_mesh");
    mmElement->SetAttribute("type", group->GetType().c_str());
    mmElement->SetAttribute("model_name", group->GetModelName().c_str());
    mmElement->SetAttribute("version", "1.0");
    document.LinkEndChild(mmElement);

    for (unsigned int t = 0; t < group->GetTimeSize(); t++) {
        auto timestepElement = document.NewElement("timestep");
        timestepElement->SetAttribute("id", (int)t);
        mmElement->LinkEndChild(timestepElement);

        auto mesh = group->GetMesh(t);
        if (!mesh) {
            continue;
        }

        auto meshElement = document.NewElement("mesh");
        timestepElement->LinkEndChild(meshElement);
        meshElement->SetAttribute("type", mesh->GetType().c_str());

        auto chElement = document.NewElement("command_history");
        meshElement->LinkEndChild(chElement);

        for (auto const& cmd : mesh->GetCommandHistory()) {
            auto cmdElement = document.NewElement("command");
            chElement->LinkEndChild(cmdElement);
            cmdElement->SetAttribute("content", cmd.c_str());
        }

        std::string surfaceFileName = fileName.substr(0, fileName.find_last_of(".")) + ".vtp";
        if (!mesh->WriteSurfaceFile(surfaceFileName)) {
            throw std::runtime_error("Error writing the surface mesh to file: " + surfaceFileName);
        }

        std::string volumeFileName = fileName.substr(0, fileName.find_last_of(".")) + ".vtu";
        if (!mesh->WriteVolumeFile(volumeFileName)) {
            throw std::runtime_error("Error writing the volume mesh to file: " + volumeFileName);
        }
    }

    if (document.SaveFile(fileName.c_str()) != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error("Could not write the mesh parameter file to " + fileName);
    }
}
