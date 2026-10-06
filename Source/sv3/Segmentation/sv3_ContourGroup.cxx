#include "tinyxml2.h"

#include "sv3_ContourGroup.h"
#include "sv3_CircleContour.h"
#include "sv3_PolygonContour.h"
#include "sv3_LevelSetContour.h"
#include "sv3_SplinePolygonContour.h"

#include <fstream>
#include <iostream>
#include <regex>

using sv3::ContourGroup;

ContourGroup::ContourGroup()
    : m_Contours(1), m_PathID(-1), m_PathName(""), m_ResliceSize(5.0),
      m_LoftingParam(new svLoftingParam())
{
}

void ContourGroup::Expand(unsigned int timeSteps) {
    unsigned int oldSize = m_Contours.size();
    if (timeSteps > oldSize) {
        m_Contours.resize(timeSteps);
    }
}

void ContourGroup::InsertContour(int contourIndex, std::unique_ptr<sv3::Contour> contour, unsigned int t) {
    this->Expand(t + 1);
    if (t < m_Contours.size()) {
        if (contourIndex == -1)
            contourIndex = m_Contours[t].size();
        
        if (contourIndex > -1 && contourIndex <= m_Contours[t].size()) {
            m_Contours[t].insert(m_Contours[t].begin() + contourIndex, std::move(contour));
        }
    }
}

void ContourGroup::SetProp(const std::string &key, std::string value) {
    m_Props[key] = value;
  }
  
std::string ContourGroup::GetProp(const std::string &key) const {
    std::map<std::string, std::string> *p =
        const_cast<std::map<std::string, std::string> *>(&m_Props);
    return (*p)[key];
}

int ContourGroup::GetSize(unsigned int t) const {
    if (t < m_Contours.size()) {
        return m_Contours[t].size();
    }
    else {
        return 0;
    }
}

sv3::Contour* ContourGroup::GetContour(int contourIndex, unsigned int t) const {
    if (t < m_Contours.size()) {
        if (contourIndex == -1)
            contourIndex = m_Contours[t].size() - 1;
        
        if ((contourIndex > -1) && contourIndex < m_Contours[t].size()) {
            return m_Contours[t][contourIndex].get();
        }
        else {
            return nullptr;
        }
    }
    else {
        return nullptr;
    }
}

static std::string trim(std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

static std::vector<std::string> split(const std::string& s, const std::string& pattern)
{
  std::regex re(pattern);
  std::vector<std::string> tokens;
  std::sregex_token_iterator it(s.begin(), s.end(), re, -1);
  std::sregex_token_iterator end;
  for (; it != end; ++it) {
    std::string token = *it;
    if (!token.empty()) {
      tokens.push_back(token);
    }
  }
  return tokens;
}

static int indexOf(const std::vector<std::string>& list, const std::string& target)
{
  for (size_t i = 0; i < list.size(); i++) {
    if (list[i] == target) {
      return static_cast<int>(i);
    }
  }
  return -1;
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

std::unique_ptr<ContourGroup> ContourGroup::CreateGroupFromFile(const std::string& fileName) {
#define n_debug_CreateGroupFromFile
#ifdef debug_CreateGroupFromFile
  std::string msg("[sv4guiContourGroupIO::CreateGroupFromFile] ");
  std::cout << msg << "========== CreateGroupFromFile ==========" << std::endl;
  std::cout << msg << "fileName: " << fileName << std::endl;
#endif

  tinyxml2::XMLDocument document;
  auto group = std::make_unique<sv3::ContourGroup>();

  if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS) {
    throw std::runtime_error("Could not open/read/parse " + fileName);
    return group;
  }

  auto groupElement = document.FirstChildElement("contourgroup");

  if (!groupElement) {
    throw std::runtime_error("No ContourGroup data in " + fileName);
  }

  group->SetPathName(groupElement->Attribute("path_name"));
  int pathID = 0;
  groupElement->QueryIntAttribute("path_id", &pathID);
  group->SetPathID(pathID);

  double resliceSize = 5.0;
  groupElement->QueryDoubleAttribute("reslice_size", &resliceSize);
  group->SetResliceSize(resliceSize);

  const char *point2dsize = "";
  const char *point3dsize = "";
  groupElement->QueryStringAttribute("point_2D_display_size", &point2dsize);
  groupElement->QueryStringAttribute("point_size", &point3dsize);
//   group->SetProp("point 2D display size", point2dsize);
//   group->SetProp("point size", point3dsize);

  int timestep = -1;

  for (auto timestepElement = groupElement->FirstChildElement("timestep");
       timestepElement != nullptr;
       timestepElement = timestepElement->NextSiblingElement("timestep")) {
    if (timestepElement == nullptr) {
      continue;
    }

    timestep++;
    group->Expand(timestep + 1);
#ifdef debug_CreateGroupFromFile
    std::cout << msg << "timestep: " << timestep << std::endl;
#endif

    // Set lofting parameters.
    //
    if (timestep == 0) {
      auto loftParamElement =
          timestepElement->FirstChildElement("lofting_parameters");
      if (loftParamElement != nullptr) {
        svLoftingParam *param = group->GetLoftingParam();

        set_string_from_attribute(loftParamElement, "method", param->method);
        // davep loftParamElement->QueryStringAttribute("method",
        // &param->method);

        loftParamElement->QueryIntAttribute("sampling",
                                            &param->numOutPtsInSegs);
        loftParamElement->QueryIntAttribute("sample_per_seg",
                                            &param->samplePerSegment);
        loftParamElement->QueryIntAttribute("use_linear_sample",
                                            &param->useLinearSampleAlongLength);
        loftParamElement->QueryIntAttribute("linear_multiplier",
                                            &param->linearMuliplier);
        loftParamElement->QueryIntAttribute("use_fft", &param->useFFT);
        loftParamElement->QueryIntAttribute("num_modes", &param->numModes);

        loftParamElement->QueryIntAttribute("u_degree", &param->uDegree);
        loftParamElement->QueryIntAttribute("v_degree", &param->vDegree);

        set_string_from_attribute(loftParamElement, "u_knot_type",
                                  param->uKnotSpanType);
        // davep
        // loftParamElement->QueryStringAttribute("u_knot_type",&param->uKnotSpanType);

        set_string_from_attribute(loftParamElement, "v_knot_type",
                                  param->vKnotSpanType);
        // davep
        // loftParamElement->QueryStringAttribute("v_knot_type",&param->vKnotSpanType);

        set_string_from_attribute(loftParamElement, "u_parametric_type",
                                  param->uParametricSpanType);
        // davep
        // loftParamElement->QueryStringAttribute("u_parametric_type",&param->uParametricSpanType);

        set_string_from_attribute(loftParamElement, "v_parametric_type",
                                  param->vParametricSpanType);
// davep
// loftParamElement->QueryStringAttribute("v_parametric_type",&param->vParametricSpanType);
#ifdef debug_CreateGroupFromFile
        std::cout << msg << "method: " << param->method << std::endl;
        std::cout << msg << "u_knot_type: " << param->uKnotSpanType
                  << std::endl;
#endif
      }
    }

    for (auto contourElement = timestepElement->FirstChildElement("contour");
         contourElement != nullptr;
         contourElement = contourElement->NextSiblingElement("contour")) {
      if (contourElement == nullptr)
        continue;

      std::string type;
      set_string_from_attribute(contourElement, "type", type);
      // davep contourElement->QueryStringAttribute("type", &type);

      std::unique_ptr<sv3::Contour> contour;

      // This mapping was adapted from ContourCtorMap in Segmentation_PyClass.cxx
      if (type == "Circle") {
        contour = std::make_unique<sv3::circleContour>();
      } else if (type == "Ellipse") {
        contour = std::make_unique<sv3::circleContour>();
      } else if (type == "Polygon") {
        contour = std::make_unique<sv3::ContourPolygon>();
      } else if (type == "SplinePolygon") {
        contour = std::make_unique<sv3::ContourSplinePolygon>();
      } else if (type == "TensionPolygon") { // Note (Jared): Not sure what to do here, using Polygon for now
        contour = std::make_unique<sv3::ContourPolygon>();
      } else {
        contour = std::make_unique<sv3::Contour>();
      }

    //   sv4guiContourEllipse *ce = dynamic_cast<sv4guiContourEllipse *>(contour);
    //   if (ce) {
    //     std::string asCircle;
    //     set_string_from_attribute(contourElement, "as_circle", asCircle);
    //     // davep contourElement->QueryStringAttribute("as_circle", &asCircle);
    //     ce->SetAsCircle(asCircle == "true" ? true : false);
    //   }

    //   sv4guiContourTensionPolygon *ct =
    //       dynamic_cast<sv4guiContourTensionPolygon *>(contour);
    //   if (ct) {
    //     int subdivisionRounds = 0;
    //     contourElement->QueryIntAttribute("subdivision_rounds",
    //                                       &subdivisionRounds);
    //     double tensionParam = 0.0;
    //     contourElement->QueryDoubleAttribute("tension_param", &tensionParam);
    //     ct->SetSubdivisionRounds(subdivisionRounds);
    //     ct->SetTensionParameter(tensionParam);
    //   }

      int contourID;
      contourElement->QueryIntAttribute("id", &contourID);
      contour->SetContourID(contourID);

      std::string method;
      set_string_from_attribute(contourElement, "method", method);
      // contourElement->QueryStringAttribute("method", &method);

      contour->SetMethod(method);
      std::string closed;
      set_string_from_attribute(contourElement, "closed", closed);
      // davep contourElement->QueryStringAttribute("closed", &closed);
      contour->SetClosed(closed == "false" ? false : true);
      int minControlNumber, maxControlNumber;
      contourElement->QueryIntAttribute("min_control_number",
                                        &minControlNumber);
      contour->SetMinControlPointNumber(minControlNumber);
      contourElement->QueryIntAttribute("max_control_number",
                                        &maxControlNumber);
      contour->SetMaxControlPointNumber(maxControlNumber);
      int subdivisionType = 0;
      contourElement->QueryIntAttribute("subdivision_type", &subdivisionType);
      int subdivisionNumber = 0;
      contourElement->QueryIntAttribute("subdivision_number",
                                        &subdivisionNumber);
      double spacing = 1.0;
      contourElement->QueryDoubleAttribute("subdivision_spacing", &spacing);
      contour->SetSubdivisionType(
          (sv3::Contour::SubdivisionType)subdivisionType);
      contour->SetSubdivisionNumber(subdivisionNumber);
      contour->SetSubdivisionSpacing(spacing);

    //   contour->SetPlaced();

      auto xml_io = sv3::XmlIOUtil(document);

      // path point
      auto pathpointElement = contourElement->FirstChildElement("path_point");
      if (pathpointElement != nullptr) {
        sv3::PathElement::PathPoint pathPoint;
        int id = 0;
        pathpointElement->QueryIntAttribute("id", &id);
        pathPoint.id = id;
        pathPoint.pos =
            xml_io.GetPoint(pathpointElement->FirstChildElement("pos"));
        pathPoint.tangent =
            xml_io.GetVector(pathpointElement->FirstChildElement("tangent"));
        pathPoint.rotation =
            xml_io.GetVector(pathpointElement->FirstChildElement("rotation"));

        contour->SetPathPoint(pathPoint);
      }

      // control points without updating contour points
      auto controlpointsElement =
          contourElement->FirstChildElement("control_points");
      if (controlpointsElement != nullptr) {
        std::vector<std::array<double,3>> controlPoints;
        for (auto pointElement =
                 controlpointsElement->FirstChildElement("point");
             pointElement != nullptr;
             pointElement = pointElement->NextSiblingElement("point")) {
          if (pointElement == nullptr)
            continue;

          controlPoints.push_back(xml_io.GetPoint(pointElement));
        }
        contour->SetControlPoints(controlPoints, false);
      }

      // contour points
      auto contourpointsElement =
          contourElement->FirstChildElement("contour_points");
      if (contourpointsElement != nullptr) {
        std::vector<std::array<double,3>> contourPoints;
        for (auto pointElement =
                 contourpointsElement->FirstChildElement("point");
             pointElement != nullptr;
             pointElement = pointElement->NextSiblingElement("point")) {
          if (pointElement == nullptr)
            continue;

          contourPoints.push_back(xml_io.GetPoint(pointElement));
        }
        contour->SetContourPoints(contourPoints, false);
        contour->ContourPointsChanged(); // Calculate contour center.
      }

      group->InsertContour(-1, std::move(contour), timestep);
    } // contour

  } // timestep

  return group;
  ;
}

std::unique_ptr<ContourGroup> ContourGroup::CreateGroupFromLegacyFile(const std::string& fileName) {

    auto contourGroup = std::make_unique<sv3::ContourGroup>();
  
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        return contourGroup;
    }
  
    std::string line;
    while (std::getline(inputFile, line)) {
        line = trim(line);
        if (line.find("/group/") == std::string::npos) {
            continue;
        }

        std::vector<std::string> list = split(line, "/");
        contourGroup->SetPathName(list[1]);

        auto contour = std::make_unique<sv3::Contour>();

        sv3::PathElement::PathPoint pathPoint;
        std::getline(inputFile, line);
        pathPoint.id = std::stoi(trim(line));

        std::getline(inputFile, line);
        list = split(line,"[(),{}\\s+]");

        int index;

        index = indexOf(list, "pathId");
        if (index != -1) {
            contourGroup->SetPathID(std::stoi(list[index + 1]));
        }

        index = indexOf(list, "pos");
        if (index != -1) {
            for (int i = 0; i < 3; i++) {
                pathPoint.pos[i] = std::stod(list[index + i + 1]);
            }
        }

        index = indexOf(list, "nrm");
        if (index != -1) {
            for (int i = 0; i < 3; i++) {
                pathPoint.tangent[i] = std::stod(list[index + i + 1]);
            }
        }

        index = indexOf(list, "xhat");
        if (index != -1) {
            for (int i = 0; i < 3; i++) {
                pathPoint.rotation[i] = std::stod(list[index + i + 1]);
            }
        }

        contour->SetPathPoint(pathPoint);
        contour->SetMethod("Legacy");
        // contour->SetPlaced();

        std::vector<std::array<double,3>> contourPoints;
        while (std::getline(inputFile, line)) {
            line = trim(line);
            if (line.empty())
                break;
            list = split(line, "\\s+");
            std::array<double,3> point;
            for (int i = 0; i < 3; i++) {
                point[i] = std::stod(list[i]);
            }
            contourPoints.push_back(point);
        }
        contour->SetContourPoints(contourPoints, false);

        contourGroup->InsertContour(-1, std::move(contour));
    }
  
    return contourGroup;
}

//-------------
// WriteToFile
//-------------
// Write a ContourGroup to a file.
//
void ContourGroup::WriteToFile(const ContourGroup* group, const std::string &fileName) {
#define n_debug_WriteToFile
#ifdef debug_WriteToFile
  std::string msg("[sv4guiContourGroupIO::WriteToFile] ");
  std::cout << msg << "========== WriteToFile ==========" << std::endl;
#endif

  tinyxml2::XMLDocument document;
  auto decl = document.NewDeclaration();
  document.LinkEndChild(decl);

  auto groupElement = document.NewElement("contourgroup");
  groupElement->SetAttribute("path_name", group->GetPathName().c_str());
  groupElement->SetAttribute("path_id", group->GetPathID());
  groupElement->SetAttribute("reslice_size", group->GetResliceSize());
  groupElement->SetAttribute("point_2D_display_size",
                             group->GetProp("point 2D display size").c_str());
  groupElement->SetAttribute("point_size",
                             group->GetProp("point size").c_str());
  groupElement->SetAttribute("version", "1.0");
  document.LinkEndChild(groupElement);

  for (int t = 0; t < group->GetTimeSize(); t++) {
    auto timestepElement = document.NewElement("timestep");
    timestepElement->SetAttribute("id", t);
    groupElement->LinkEndChild(timestepElement);

    if (t == 0) {
      auto loftParamElement = document.NewElement("lofting_parameters");
      timestepElement->LinkEndChild(loftParamElement);
      svLoftingParam *param = group->GetLoftingParam();
      loftParamElement->SetAttribute("method", param->method.c_str());

      loftParamElement->SetAttribute("sampling", param->numOutPtsInSegs);
      loftParamElement->SetAttribute("sample_per_seg", param->samplePerSegment);
      loftParamElement->SetAttribute("use_linear_sample",
                                     param->useLinearSampleAlongLength);
      loftParamElement->SetAttribute("linear_multiplier",
                                     param->linearMuliplier);
      loftParamElement->SetAttribute("use_fft", param->useFFT);
      loftParamElement->SetAttribute("num_modes", param->numModes);

      loftParamElement->SetAttribute("u_degree", param->uDegree);
      loftParamElement->SetAttribute("v_degree", param->vDegree);
      loftParamElement->SetAttribute("u_knot_type",
                                     param->uKnotSpanType.c_str());
      loftParamElement->SetAttribute("v_knot_type",
                                     param->vKnotSpanType.c_str());
      loftParamElement->SetAttribute("u_parametric_type",
                                     param->uParametricSpanType.c_str());
      loftParamElement->SetAttribute("v_parametric_type",
                                     param->vParametricSpanType.c_str());
    }

    auto xml_io = sv3::XmlIOUtil(document);

    for (int i = 0; i < group->GetSize(t); i++) {
      auto contour = group->GetContour(i, t);
      if (!contour) {
        continue;
      }

      auto contourElement = document.NewElement("contour");
      timestepElement->LinkEndChild(contourElement);
      std::string type = contour->GetType();
      contourElement->SetAttribute("id", i);
      contourElement->SetAttribute("type", type.c_str());
      contourElement->SetAttribute("method", contour->GetMethod().c_str());
      contourElement->SetAttribute("closed",
                                   contour->IsClosed() ? "true" : "false");
      contourElement->SetAttribute("min_control_number",
                                   contour->GetMinControlPointNumber());
      contourElement->SetAttribute("max_control_number",
                                   contour->GetMaxControlPointNumber());
      contourElement->SetAttribute("subdivision_type",
                                   contour->GetSubdivisionType());
      contourElement->SetAttribute("subdivision_number",
                                   contour->GetSubdivisionNumber());
      contourElement->SetAttribute("subdivision_spacing",
                                   contour->GetSubdivisionSpacing());

    // TODO (Jared): Do these need to be fixed?                                    
    //   auto ce = dynamic_cast<sv4guiContourEllipse *>(contour);
    //   if (ce) {
    //     contourElement->SetAttribute("as_circle",
    //                                  ce->AsCircle() ? "true" : "false");
    //   }

    //   auto ct = dynamic_cast<sv4guiContourTensionPolygon *>(contour);
    //   if (ct) {
    //     contourElement->SetAttribute("subdivision_rounds",
    //                                  ct->GetSubdivisionRounds());
    //     contourElement->SetAttribute("tension_param",
    //                                  ct->GetTensionParameter());
    //   }

      // path point
      auto pathpointElement = document.NewElement("path_point");
      contourElement->LinkEndChild(pathpointElement);
      pathpointElement->SetAttribute("id", contour->GetPathPoint().id);

      // [DaveP] careful with these calls, have CreateXMLPointElement() in
      // sv3_XmlIOUtil.h and sv4gui_XmlIOUtil.h.
      pathpointElement->LinkEndChild(
          xml_io.CreateXMLPointElement("pos", contour->GetPathPoint().pos));
      pathpointElement->LinkEndChild(xml_io.CreateXMLVectorElement(
          "tangent", contour->GetPathPoint().tangent));
      pathpointElement->LinkEndChild(xml_io.CreateXMLVectorElement(
          "rotation", contour->GetPathPoint().rotation));
      // pathpointElement->LinkEndChild(sv4guiXmlIOUtil::CreateXMLPointElement("pos",contour->GetPathPoint().pos));
      // pathpointElement->LinkEndChild(sv4guiXmlIOUtil::CreateXMLVectorElement("tangent",contour->GetPathPoint().tangent));
      // pathpointElement->LinkEndChild(sv4guiXmlIOUtil::CreateXMLVectorElement("rotation",contour->GetPathPoint().rotation));

      // control points
      auto controlpointsElement = document.NewElement("control_points");
      contourElement->LinkEndChild(controlpointsElement);
      for (int j = 0; j < contour->GetControlPointNumber(); j++) {
        controlpointsElement->LinkEndChild(xml_io.CreateXMLPointElement(
            "point", j, contour->GetControlPoint(j)));
        // controlpointsElement->LinkEndChild(sv4guiXmlIOUtil::CreateXMLPointElement("point",j,contour->GetControlPoint(j)));
      }

      // contour points
      auto contourpointsElement = document.NewElement("contour_points");
      contourElement->LinkEndChild(contourpointsElement);
      for (int j = 0; j < contour->GetContourPointNumber(); j++) {
        contourpointsElement->LinkEndChild(xml_io.CreateXMLPointElement(
            "point", j, contour->GetContourPoint(j)));
        // davep
        // contourpointsElement->LinkEndChild(sv4guiXmlIOUtil::CreateXMLPointElement("point",j,contour->GetContourPoint(j)));
      }
    }
  }

  if (document.SaveFile(fileName.c_str()) != tinyxml2::XML_SUCCESS) {
    std::runtime_error("Could not write contourgroup to the file " + fileName);
  }
}   
