#include "sv3_ModelGroup.h"

#include <tinyxml2.h>

#include <stdexcept>

using sv3::ModelGroup;
using sv3::ModelElement;

ModelGroup::ModelGroup()
    : m_Type()
{
}

void ModelGroup::Expand(unsigned int timeSteps)
{
    if (timeSteps > m_Models.size()) {
        m_Models.resize(timeSteps);
    }
}

ModelElement* ModelGroup::GetModelElement(unsigned int t) const
{
    if (t < m_Models.size()) {
        return m_Models[t].get();
    }
    return nullptr;
}

void ModelGroup::SetModelElement(std::unique_ptr<ModelElement> model, unsigned int t)
{
    Expand(t + 1);
    m_Models[t] = std::move(model);
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
// Create a ModelGroup from a .mdl file.
//
// Ported from sv4guiModelIO::CreateGroupFromFile()
// (Source/sv4gui/Modules/_Model/_Common/sv4gui_ModelIO.cxx) to remove
// _PythonAPI's dependency on sv4gui/MITK, reading the same XML schema so
// files remain interchangeable with the sv4gui GUI.
//
std::unique_ptr<ModelGroup> ModelGroup::CreateGroupFromFile(const std::string& fileName)
{
    tinyxml2::XMLDocument document;
    auto group = std::make_unique<ModelGroup>();

    if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error("Could not open/read/parse " + fileName);
    }

    auto modelElement = document.FirstChildElement("model");
    if (!modelElement) {
        throw std::runtime_error("No Model data in " + fileName);
    }

    const char* modelType = "";
    modelElement->QueryStringAttribute("type", &modelType);
    group->SetType(modelType);

    int timestep = -1;

    for (auto timestepElement = modelElement->FirstChildElement("timestep");
         timestepElement != nullptr;
         timestepElement = timestepElement->NextSiblingElement("timestep")) {
        timestep++;
        group->Expand(timestep + 1);

        auto meElement = timestepElement->FirstChildElement("model_element");
        if (meElement == nullptr) {
            continue;
        }

        std::string type;
        set_string_from_attribute(meElement, "type", type);
        if (type.empty()) {
            throw std::runtime_error("No type info available when trying to load the model");
        }

        auto me = std::make_unique<ModelElement>();
        me->SetType(type);

        // Read the element's native geometry file (same base name as the
        // .mdl file, with the element's native extension).
        std::string fileExtension;
        auto exts = me->GetFileExtensions();
        if (!exts.empty()) {
            fileExtension = exts[0];
        }
        if (fileExtension.empty()) {
            throw std::runtime_error("No file extension available for model type: " + type);
        }

        std::string dataFileName = fileName.substr(0, fileName.find_last_of(".")) + "." + fileExtension;

        if (!me->ReadFile(dataFileName)) {
            throw std::runtime_error("Failed in reading: " + dataFileName);
        }

        if (type != "PolyData") {
            double maxDist = me->GetMaxDist();
            if (meElement->QueryDoubleAttribute("max_dist", &maxDist) == tinyxml2::XML_SUCCESS) {
                me->SetMaxDist(maxDist);
            }
            me->SetWholeVtkPolyData(me->CreateWholeVtkPolyData());
        }

        int numSampling = 0;
        meElement->QueryIntAttribute("num_sampling", &numSampling);
        me->SetNumSampling(numSampling);

        int useUniform = me->IfUseUniform();
        meElement->QueryIntAttribute("use_uniform", &useUniform);
        me->SetUseUniform(useUniform);

        if (useUniform) {
            auto param = me->GetLoftingParam();

            set_string_from_attribute(meElement, "method", param->method);

            meElement->QueryIntAttribute("sampling", &param->numOutPtsInSegs);
            meElement->QueryIntAttribute("sample_per_seg", &param->samplePerSegment);
            meElement->QueryIntAttribute("use_linear_sample", &param->useLinearSampleAlongLength);
            meElement->QueryIntAttribute("linear_multiplier", &param->linearMuliplier);
            meElement->QueryIntAttribute("use_fft", &param->useFFT);
            meElement->QueryIntAttribute("num_modes", &param->numModes);

            meElement->QueryIntAttribute("u_degree", &param->uDegree);
            meElement->QueryIntAttribute("v_degree", &param->vDegree);

            set_string_from_attribute(meElement, "u_knot_type", param->uKnotSpanType);
            set_string_from_attribute(meElement, "v_knot_type", param->vKnotSpanType);
            set_string_from_attribute(meElement, "u_parametric_type", param->uParametricSpanType);
            set_string_from_attribute(meElement, "v_parametric_type", param->vParametricSpanType);
        }

        auto facesElement = meElement->FirstChildElement("faces");
        if (facesElement != nullptr) {
            std::vector<ModelElement::ModelFace> faces;
            for (auto faceElement = facesElement->FirstChildElement("face");
                 faceElement != nullptr;
                 faceElement = faceElement->NextSiblingElement("face")) {
                ModelElement::ModelFace face;

                int id = 0;
                faceElement->QueryIntAttribute("id", &id);
                face.id = id;

                set_string_from_attribute(faceElement, "name", face.name);
                set_string_from_attribute(faceElement, "type", face.type);

                std::string isVisible = "true";
                set_string_from_attribute(faceElement, "visible", isVisible);
                face.visible = (isVisible == "true");

                float opacity = 1.0f;
                faceElement->QueryFloatAttribute("opacity", &opacity);
                face.opacity = opacity;

                float color1 = 1.0f, color2 = 1.0f, color3 = 1.0f;
                faceElement->QueryFloatAttribute("color1", &color1);
                faceElement->QueryFloatAttribute("color2", &color2);
                faceElement->QueryFloatAttribute("color3", &color3);
                face.color[0] = color1;
                face.color[1] = color2;
                face.color[2] = color3;

                faces.push_back(face);
            }
            me->SetFaces(faces);
        }

        auto segsElement = meElement->FirstChildElement("segmentations");
        if (segsElement != nullptr) {
            std::vector<std::string> segNames;
            for (auto segElement = segsElement->FirstChildElement("seg");
                 segElement != nullptr;
                 segElement = segElement->NextSiblingElement("seg")) {
                std::string name;
                set_string_from_attribute(segElement, "name", name);
                segNames.push_back(name);
            }
            me->SetSegNames(segNames);
        }

        auto blendRadiiElement = meElement->FirstChildElement("blend_radii");
        if (blendRadiiElement != nullptr) {
            std::vector<ModelElement::BlendParamRadius> blendRadii;
            for (auto radiusElement = blendRadiiElement->FirstChildElement("face_pair");
                 radiusElement != nullptr;
                 radiusElement = radiusElement->NextSiblingElement("face_pair")) {
                ModelElement::BlendParamRadius radius;
                radiusElement->QueryIntAttribute("face_id1", &radius.faceID1);
                radiusElement->QueryIntAttribute("face_id2", &radius.faceID2);
                radiusElement->QueryDoubleAttribute("radius", &radius.radius);
                // Faces were already read above, so these lookups succeed here.
                radius.faceName1 = me->GetFaceName(radius.faceID1);
                radius.faceName2 = me->GetFaceName(radius.faceID2);
                blendRadii.push_back(radius);
            }
            me->SetBlendRadii(blendRadii);
        }

        // Blend parameter attribute names deliberately match sv4gui_ModelIO.cxx's
        // read side exactly (including its "iter" vs "iters" mismatch against the
        // write side below) so files stay interchangeable with the sv4gui GUI.
        if (type == "PolyData") {
            auto blendElement = meElement->FirstChildElement("blend_param");
            if (blendElement != nullptr) {
                auto param = me->GetBlendParam();
                blendElement->QueryIntAttribute("blend_iters", &param->numblenditers);
                blendElement->QueryIntAttribute("sub_blend_iter", &param->numsubblenditers);
                blendElement->QueryIntAttribute("cstr_smooth_iter", &param->numcgsmoothiters);
                blendElement->QueryIntAttribute("lap_smooth_iter", &param->numlapsmoothiters);
                blendElement->QueryIntAttribute("subdivision_iters", &param->numsubdivisioniters);
                blendElement->QueryDoubleAttribute("decimation", &param->targetdecimation);
            }
        }

        // Parasolid's internal face numbering can differ from what was saved in
        // the .mdl file, so re-derive face IDs from the reloaded solid via its
        // (name-keyed) face attributes rather than trusting the saved IDs.
        if (type == "Parasolid") {
            auto blendRadii = me->GetBlendRadii();
            for (auto& radius : blendRadii) {
                radius.faceName1 = me->GetFaceName(radius.faceID1);
                radius.faceName2 = me->GetFaceName(radius.faceID2);
            }

            auto faces = me->GetFaces();
            for (auto& face : faces) {
                face.id = me->GetFaceIDFromInnerSolid(face.name);
            }
            me->SetFaces(faces);

            for (auto& radius : blendRadii) {
                radius.faceID1 = me->GetFaceID(radius.faceName1);
                radius.faceID2 = me->GetFaceID(radius.faceName2);
            }
            me->SetBlendRadii(blendRadii);
        }

        group->SetModelElement(std::move(me), timestep);
    } // timestep

    return group;
}

//------------------
// WriteToFile
//------------------
// Write a ModelGroup to a .mdl file.
//
// Ported from sv4guiModelIO::WriteGroupToFile()
// (Source/sv4gui/Modules/_Model/_Common/sv4gui_ModelIO.cxx).
//
void ModelGroup::WriteToFile(const ModelGroup* group, const std::string& fileName)
{
    tinyxml2::XMLDocument document;
    auto decl = document.NewDeclaration();
    document.LinkEndChild(decl);

    auto modelElement = document.NewElement("model");
    modelElement->SetAttribute("type", group->GetType().c_str());
    modelElement->SetAttribute("version", "1.0");
    document.LinkEndChild(modelElement);

    for (unsigned int t = 0; t < group->GetTimeSize(); t++) {
        auto timestepElement = document.NewElement("timestep");
        timestepElement->SetAttribute("id", (int)t);
        modelElement->LinkEndChild(timestepElement);

        auto me = group->GetModelElement(t);
        if (!me) {
            continue;
        }

        auto meElement = document.NewElement("model_element");
        timestepElement->LinkEndChild(meElement);
        meElement->SetAttribute("type", me->GetType().c_str());
        meElement->SetAttribute("num_sampling", me->GetNumSampling());
        meElement->SetAttribute("use_uniform", me->IfUseUniform());

        if (me->IfUseUniform()) {
            auto param = me->GetLoftingParam();
            meElement->SetAttribute("method", param->method.c_str());

            meElement->SetAttribute("sampling", param->numOutPtsInSegs);
            meElement->SetAttribute("sample_per_seg", param->samplePerSegment);
            meElement->SetAttribute("use_linear_sample", param->useLinearSampleAlongLength);
            meElement->SetAttribute("linear_multiplier", param->linearMuliplier);
            meElement->SetAttribute("use_fft", param->useFFT);
            meElement->SetAttribute("num_modes", param->numModes);

            meElement->SetAttribute("u_degree", param->uDegree);
            meElement->SetAttribute("v_degree", param->vDegree);
            meElement->SetAttribute("u_knot_type", param->uKnotSpanType.c_str());
            meElement->SetAttribute("v_knot_type", param->vKnotSpanType.c_str());
            meElement->SetAttribute("u_parametric_type", param->uParametricSpanType.c_str());
            meElement->SetAttribute("v_parametric_type", param->vParametricSpanType.c_str());
        }

        auto segsElement = document.NewElement("segmentations");
        meElement->LinkEndChild(segsElement);

        for (auto const& name : me->GetSegNames()) {
            auto segElement = document.NewElement("seg");
            segsElement->LinkEndChild(segElement);
            segElement->SetAttribute("name", name.c_str());
        }

        auto facesElement = document.NewElement("faces");
        meElement->LinkEndChild(facesElement);

        for (auto const& face : me->GetFaces()) {
            auto faceElement = document.NewElement("face");
            facesElement->LinkEndChild(faceElement);
            faceElement->SetAttribute("id", face.id);
            faceElement->SetAttribute("name", face.name.c_str());
            faceElement->SetAttribute("type", face.type.c_str());
            faceElement->SetAttribute("visible", face.visible ? "true" : "false");
            faceElement->SetAttribute("opacity", face.opacity);
            faceElement->SetAttribute("color1", face.color[0]);
            faceElement->SetAttribute("color2", face.color[1]);
            faceElement->SetAttribute("color3", face.color[2]);
        }

        // Radii for blending.
        auto blendRadiiElement = document.NewElement("blend_radii");
        meElement->LinkEndChild(blendRadiiElement);
        for (auto const& radius : me->GetBlendRadii()) {
            auto radiusElement = document.NewElement("face_pair");
            blendRadiiElement->LinkEndChild(radiusElement);
            radiusElement->SetAttribute("face_id1", radius.faceID1);
            radiusElement->SetAttribute("face_id2", radius.faceID2);
            radiusElement->SetAttribute("radius", radius.radius);
        }

        if (me->GetType() == "PolyData") {
            auto blendElement = document.NewElement("blend_param");
            meElement->LinkEndChild(blendElement);
            auto param = me->GetBlendParam();

            blendElement->SetAttribute("blend_iters", param->numblenditers);
            blendElement->SetAttribute("sub_blend_iters", param->numsubblenditers);
            blendElement->SetAttribute("cstr_smooth_iters", param->numcgsmoothiters);
            blendElement->SetAttribute("lap_smooth_iters", param->numlapsmoothiters);
            blendElement->SetAttribute("subdivision_iters", param->numsubdivisioniters);
            blendElement->SetAttribute("decimation", param->targetdecimation);
        }

        if (me->GetType() != "PolyData") {
            meElement->SetAttribute("max_dist", me->GetMaxDist());
        }

        // Output the element's native geometry file.
        std::string fileExtension;
        auto exts = me->GetFileExtensions();
        if (!exts.empty()) {
            fileExtension = exts[0];
        }
        if (fileExtension.empty()) {
            throw std::runtime_error("No file extension available for model type: " + me->GetType());
        }

        std::string dataFileName = fileName.substr(0, fileName.find_last_of("."));
        if (me->GetType() != "Parasolid") {
            dataFileName = dataFileName + "." + fileExtension;
        }

        if (!me->WriteFile(dataFileName)) {
            throw std::runtime_error("Failed to write model to " + dataFileName);
        }
    }

    if (document.SaveFile(fileName.c_str()) != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error("Could not write Model parameters to the file " + fileName);
    }
}
