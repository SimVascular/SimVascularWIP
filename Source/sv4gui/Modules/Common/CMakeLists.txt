set(vtkSV4Common_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModuleCommonExports.h)
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
    BASE_NAME "SV4GUIMODULECOMMON"
    EXPORT_FILE_NAME ${vtkSV4Common_EXPORT_HEADER}
)
vtk_module_link(VTK::SV4Common PUBLIC MitkCore)