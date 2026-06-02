set(vtkSV1Utils_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svUtilsExports.h)
set(vtkSV1Utils_HEADERS
    sv_FactoryRegistrar.h
    sv_vtk_utils.h
    sv_misc_utils.h
    sv_Math.h
    sv_cgeom.h
    sv_LispList.hxx
    ${vtkSV1Utils_EXPORT_HEADER}
)

set(vtkSV1Utils_SOURCES
    sv_Math.cxx
    sv_FactoryRegistrar.cxx
    sv_vtk_utils.cxx
    sv_misc_utils.cxx
    sv_cgeom.cxx
)

vtk_module_add_module(VTK::SV1Utils
    HEADERS ${vtkSV1Utils_HEADERS}
    SOURCES ${vtkSV1Utils_SOURCES}
)
generate_export_header(VTK::SV1Utils
    EXPORT_MACRO_NAME "SV_EXPORT_UTILS"
    EXPORT_FILE_NAME ${vtkSV1Utils_EXPORT_HEADER}
)