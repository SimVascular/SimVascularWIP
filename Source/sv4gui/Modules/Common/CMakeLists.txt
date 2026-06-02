set(vtkSV4Common_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svCommonExports.h)
set(vtkSV4Common_HEADERS
    sv4gui_StringUtils.h
    sv4gui_XmlIOUtil.h
    sv4gui_VtkUtils.h
    sv4gui_VtkParametricSpline.h
    sv4gui_Spline.h
    sv4gui_Math3.h
    ${vtkSV4Common_EXPORT_HEADER}
)

set(vtkSV4Common_SOURCES
    sv4gui_StringUtils.cxx
    sv4gui_Math3.cxx
    sv4gui_Spline.cxx
    sv4gui_VtkUtils.cxx
    sv4gui_VtkParametricSpline.cxx
    sv4gui_XmlIOUtil.cxx
)

vtk_module_add_module(VTK::SV4Common
    HEADERS ${vtkSV4Common_HEADERS}
    SOURCES ${vtkSV4Common_SOURCES}
)
generate_export_header(VTK::SV4Common
    EXPORT_MACRO_NAME "SV_EXPORT_COMMON"
    EXPORT_FILE_NAME ${vtkSV4Common_EXPORT_HEADER}
)