set(vtkSV3Common_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv3CommonExports.h)
set(vtkSV3Common_HEADERS
    sv3_XmlIOUtil.h
    ${vtkSV3Common_EXPORT_HEADER}
)

set(vtkSV3Common_SOURCES
    sv3_XmlIOUtil.cxx
)

vtk_module_add_module(VTK::SV3Common
    HEADERS ${vtkSV3Common_HEADERS}
    SOURCES ${vtkSV3Common_SOURCES}
)
generate_export_header(VTK::SV3Common
    EXPORT_MACRO_NAME "SV_EXPORT_COMMON"
    EXPORT_FILE_NAME ${vtkSV3Common_EXPORT_HEADER}
)

vtk_module_link(VTK::SV3Common PUBLIC tinyxml2)  # todo superbuild