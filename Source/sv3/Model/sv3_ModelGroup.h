// sv3_ModelGroup.h
//
// Lightweight, MITK-free replacement for sv4guiModel.
// Stores a time-varying series of models as modelGroup[time].
//
#ifndef SV3_MODELGROUP_H
#define SV3_MODELGROUP_H

#include <memory>
#include <string>
#include <vector>

#include "sv3_ModelElement.h"

#include <vtkSV3ModelModule.h>

namespace sv3 {

class VTKSV3MODEL_EXPORT ModelGroup {
public:
    ModelGroup();

    std::string GetType() const { return m_Type; }
    void SetType(const std::string& type) { m_Type = type; }

    unsigned int GetTimeSize() const { return m_Models.size(); }
    void Expand(unsigned int timeSteps);

    ModelElement* GetModelElement(unsigned int t = 0) const;
    void SetModelElement(std::unique_ptr<ModelElement> model, unsigned int t = 0);

    static std::unique_ptr<ModelGroup> CreateGroupFromFile(const std::string& fileName);
    static void WriteToFile(const ModelGroup* group, const std::string& fileName);

private:
    std::string m_Type;
    std::vector<std::unique_ptr<ModelElement>> m_Models;
};

} // namespace sv3

#endif // SV3_MODELGROUP_H
