set(vtkSV1Geometry_HEADERS
    sv_cgeom.h
    sv_ggems.h
    sv_integrate_surface.h
    sv_spline.h
    sv_sys_geom.h
)

set(vtkSV1Geometry_SOURCES
    sv_ggems.cxx
    sv_integrate_surface.cxx
    sv_spline.cxx
    sv_sys_geom.cxx
    sv_cgeom.cxx
)

vtk_module_add_module(VTK::SV1Geometry
    HEADERS ${vtkSV1Geometry_HEADERS}
    SOURCES ${vtkSV1Geometry_SOURCES}
)