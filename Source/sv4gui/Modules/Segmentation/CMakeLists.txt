set(vtkSV4Segmentation_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModuleSegmentationExports.h)
set(vtkSV4Segmentation_HEADERS
    sv4gui_ContourModelThresholdInteractor.h
    sv4gui_MitkSeg3DDataInteractor.h
    sv4gui_MitkSeg3DOperation.h
    sv4gui_ContourGroupVtkMapper2D.h
    sv4gui_ContourTensionPolygon.h
    sv4gui_Surface.h
    sv4gui_SegmentationLegacyIO.h
    sv4gui_ContourOperation.h
    sv4gui_ContourGroupIO.h
    sv4gui_MitkSeg3DIO.h
    sv4gui_Seg3D.h
    sv4gui_Contour.h
    sv4gui_ContourGroupVtkMapper3D.h
    sv4gui_ContourModel.h
    sv4gui_SegmentationObjectFactory.h
    sv4gui_ContourGroup.h
    sv4gui_ContourSplinePolygon.h
    sv4gui_ContourGroupDataInteractor.h
    sv4gui_ContourModelVtkMapper2D.h
    sv4gui_MitkSeg3D.h
    sv4gui_MitkSeg3DVtkMapper3D.h
    sv4gui_ContourCircle.h
    sv4gui_SegmentationUtils.h
    sv4gui_ContourEllipse.h
    sv4gui_SurfaceVtkMapper3D.h
    sv4gui_Seg3DUtils.h
    sv4gui_ContourPolygon.h
    ${vtkSV4Segmentation_EXPORT_HEADER}
)

set(vtkSV4Segmentation_SOURCES
    sv4gui_SegmentationLegacyIO.cxx
    sv4gui_Seg3DUtils.cxx
    sv4gui_SegmentationUtils.cxx
    sv4gui_ContourGroup.cxx
    sv4gui_ContourGroupDataInteractor.cxx
    sv4gui_ContourGroupVtkMapper2D.cxx
    sv4gui_ContourSplinePolygon.cxx
    sv4gui_ContourModelThresholdInteractor.cxx
    sv4gui_ContourOperation.cxx
    sv4gui_ContourModelVtkMapper2D.cxx
    sv4gui_MitkSeg3DOperation.cxx
    sv4gui_ContourModel.cxx
    sv4gui_ContourCircle.cxx
    sv4gui_ContourTensionPolygon.cxx
    sv4gui_MitkSeg3DVtkMapper3D.cxx
    sv4gui_ContourGroupVtkMapper3D.cxx
    sv4gui_Contour.cxx
    sv4gui_Seg3D.cxx
    sv4gui_ContourGroupIO.cxx
    sv4gui_MitkSeg3DIO.cxx
    sv4gui_ContourEllipse.cxx
    sv4gui_Surface.cxx
    sv4gui_SegmentationObjectFactory.cxx
    sv4gui_SurfaceVtkMapper3D.cxx
    sv4gui_MitkSeg3DDataInteractor.cxx
    sv4gui_MitkSeg3D.cxx
    sv4gui_ContourPolygon.cxx
)

vtk_module_add_module(VTK::SV4Segmentation
    HEADERS ${vtkSV4Segmentation_HEADERS}
    SOURCES ${vtkSV4Segmentation_SOURCES}
)
generate_export_header(VTK::SV4Segmentation
    BASE_NAME "SV4GUIMODULESEGMENTATION"
    EXPORT_FILE_NAME ${vtkSV4Segmentation_EXPORT_HEADER}
)