set(vtkSV3Segmentation_HEADERS
    sv3_CircleContour.h
    sv3_SegmentationUtils.h
    sv3_ThresholdContour.h
    sv3_Contour.h
    sv3_LevelSetContour.h
    sv3_SplinePolygonContour.h
    sv3_PolygonContour.h
    sv3_ContourGroup.h
)

set(vtkSV3Segmentation_SOURCES
    sv3_Contour.cxx
    sv3_ThresholdContour.cxx
    sv3_SplinePolygonContour.cxx
    sv3_LevelSetContour.cxx
    sv3_SegmentationUtils.cxx
    sv3_CircleContour.cxx
    sv3_PolygonContour.cxx
    sv3_ContourGroup.cxx
)

vtk_module_add_module(VTK::SV3Segmentation
    HEADERS ${vtkSV3Segmentation_HEADERS}
    SOURCES ${vtkSV3Segmentation_SOURCES}
)