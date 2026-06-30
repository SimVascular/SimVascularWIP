// ContourGroup.h
//
// Lightweight, MITK-free replacement for sv4guiContourGroup.
// Stores a time-varying series of contours as contourGroup[time][id].
//
#ifndef SV3_CONTOURGROUP_H
#define SV3_CONTOURGROUP_H

#include <vector>
#include <memory>
#include <string>

#include "sv3_Contour.h"
#include "sv3_XmlIOUtil.h"

#include <vtkSV3SegmentationModule.h>

struct VTKSV3SEGMENTATION_EXPORT svLoftingParam {
    std::string method;
    
    // Spline Lofting
    int numOutPtsInSegs; // sampleDefault
    // std::vector<int> overrides;
    int samplePerSegment;
    int useLinearSampleAlongLength;
    int linearMuliplier;
    int useFFT;
    int numModes;
    
    int addCaps;
    // int noInterOut;
    int vecFlag;
    
    // int numSegs=0;
    int numOutPtsAlongLength;            //=samplePerSegment*numSegs
    int numPtsInLinearSampleAlongLength; //=linearMuliplier*numOutPtsAlongLength
    int splineType;
    
    int numSuperPts; // the number of points of the contour with the maximum point
                        // number
    
    double bias;
    double tension;
    double continuity;
    
    // Nurbs Lofting
    int uDegree;
    int vDegree;
    std::string uKnotSpanType;
    std::string vKnotSpanType;
    std::string uParametricSpanType;
    std::string vParametricSpanType;
    
    svLoftingParam()
        : method("nurbs"), numOutPtsInSegs(60), samplePerSegment(12),
            useLinearSampleAlongLength(1), linearMuliplier(10), useFFT(0),
            numModes(20), addCaps(0)
            //, noInterOut(1)
            ,
            vecFlag(0), numOutPtsAlongLength(0), numPtsInLinearSampleAlongLength(0),
            splineType(0), numSuperPts(0), bias(0), tension(0), continuity(0),
            uDegree(2), vDegree(2), uKnotSpanType("derivative"),
            vKnotSpanType("average"), uParametricSpanType("centripetal"),
            vParametricSpanType("chord")
    
    {}
    
    svLoftingParam(const svLoftingParam &other)
        : method(other.method), numOutPtsInSegs(other.numOutPtsInSegs),
            samplePerSegment(other.samplePerSegment),
            useLinearSampleAlongLength(other.useLinearSampleAlongLength),
            linearMuliplier(other.linearMuliplier), useFFT(other.useFFT),
            numModes(other.numModes), addCaps(other.addCaps)
            //, noInterOut(other.noInterOut)
            ,
            vecFlag(other.vecFlag),
            numOutPtsAlongLength(other.numOutPtsAlongLength),
            numPtsInLinearSampleAlongLength(other.numPtsInLinearSampleAlongLength),
            splineType(other.splineType), numSuperPts(other.numSuperPts),
            bias(other.bias), tension(other.tension), continuity(other.continuity),
            uDegree(other.uDegree), vDegree(other.vDegree),
            uKnotSpanType(other.uKnotSpanType), vKnotSpanType(other.vKnotSpanType),
            uParametricSpanType(other.uParametricSpanType),
            vParametricSpanType(other.vParametricSpanType) {}
    };

namespace sv3 {
class VTKSV3SEGMENTATION_EXPORT ContourGroup {
public:
    ContourGroup();

    std::string GetPathName() const { return m_PathName; }
    void SetPathName(std::string name) { m_PathName = name; }

    int GetPathID() const { return m_PathID; }
    void SetPathID(int id) { m_PathID = id; }

    double GetResliceSize() const { return m_ResliceSize; }
    void SetResliceSize(double size) { m_ResliceSize = size; }

    void SetProp(const std::string &key, std::string value);
    std::string GetProp(const std::string &key) const;
    std::map<std::string, std::string> GetProps() { return m_Props; }

    svLoftingParam *GetLoftingParam() const { return m_LoftingParam; }

    virtual unsigned int GetTimeSize() const { return m_Contours.size(); }

    virtual int GetSize(unsigned int t = 0) const;

    virtual sv3::Contour* GetContour(int contourIndex, unsigned int t = 0) const;

    void Expand(unsigned int timeSteps);
    void InsertContour(int contourIndex, std::unique_ptr<sv3::Contour> contour, unsigned int t = 0);

    static std::unique_ptr<ContourGroup> CreateGroupFromFile(const std::string& fileName);
    static std::unique_ptr<ContourGroup> CreateGroupFromLegacyFile(const std::string& fileName);

    static void WriteToFile(const ContourGroup* group, const std::string &filename);

private:
  std::vector< std::vector< std::unique_ptr<sv3::Contour>>> m_Contours;
  
  int m_PathID;

  std::string m_PathName;

  double m_ResliceSize;

  std::map<std::string, std::string> m_Props;

  svLoftingParam *m_LoftingParam;
};

} // namespace sv3
#endif // SV3_CONTOURGROUP_H
