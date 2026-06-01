set(vtkSV4ModelOCCT_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModuleModelOCCTExports.h)
set(vtkSV4ModelOCCT_HEADERS
    sv4gui_ModelUtilsOCCT.h
    sv4gui_RegisterOCCTFunction.h
    sv4gui_ModelElementOCCT.h
    ${vtkSV4ModelOCCT_EXPORT_HEADER}
)

set(vtkSV4ModelOCCT_SOURCES
    sv4gui_ModelElementOCCT.cxx
    sv4gui_ModelUtilsOCCT.cxx
    sv4gui_RegisterOCCTFunction.cxx
)

vtk_module_add_module(VTK::SV4ModelOCCT
    HEADERS ${vtkSV4ModelOCCT_HEADERS}
    SOURCES ${vtkSV4ModelOCCT_SOURCES}
)
generate_export_header(VTK::SV4ModelOCCT
    BASE_NAME "SV4GUIMODULEMODELOCCT"
    EXPORT_FILE_NAME ${vtkSV4ModelOCCT_EXPORT_HEADER}
)