set(vtkSV4ImageProcessing_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModuleImageProcessingExports.h)
set(vtkSV4ImageProcessing_HEADERS
    sv4gui_ImageProcessingUtils.h
    ${vtkSV4ImageProcessing_EXPORT_HEADER}
)

set(vtkSV4ImageProcessing_SOURCES
    sv4gui_ImageProcessingUtils.cxx
)

vtk_module_add_module(VTK::SV4ImageProcessing
    HEADERS ${vtkSV4ImageProcessing_HEADERS}
    SOURCES ${vtkSV4ImageProcessing_SOURCES}
)
generate_export_header(VTK::SV4ImageProcessing
    BASE_NAME "SV4GUIMODULEIMAGEPROCESSING"
    EXPORT_FILE_NAME ${vtkSV4ImageProcessing_EXPORT_HEADER}
)