set(vtkSV1Geometry_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svGeometryExports.h)
set(vtkSV1Geometry_HEADERS
    sv_ggems.h
    sv_sys_geom.h
    sv_spline.h
    sv_integrate_surface.h
    ${vtkSV1Geometry_EXPORT_HEADER}
)

set(vtkSV1Geometry_SOURCES
    sv_spline.cxx
    sv_sys_geom.cxx
    sv_ggems.cxx
    sv_integrate_surface.cxx
)

vtk_module_add_module(VTK::SV1Geometry
    HEADERS ${vtkSV1Geometry_HEADERS}
    SOURCES ${vtkSV1Geometry_SOURCES}
)
generate_export_header(VTK::SV1Geometry
    EXPORT_MACRO_NAME "SV_EXPORT_SYSGEOM"
    EXPORT_FILE_NAME ${vtkSV1Geometry_EXPORT_HEADER}
)