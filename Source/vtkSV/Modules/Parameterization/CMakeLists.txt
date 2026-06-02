set(vtkSVParameterization_HEADERS
    vtkSVSquareBoundaryMapper.h
    vtkSVSphericalMapper.h
    vtkSVNewParameterizeSurfaceOnPolycube.h
    vtkSVPlanarMapper.h
    vtkSVPointSetBoundaryMapper.h
    vtkSVSuperSquareBoundaryMapper.h
    vtkSVBoundaryMapper.h
    vtkSVParameterizeSurfaceOnPolycube.h
    vtkSVParameterizeVolumeOnPolycube.h
)

set(vtkSVParameterization_SOURCES
    vtkSVBoundaryMapper.cxx
    vtkSVNewParameterizeSurfaceOnPolycube.cxx
    vtkSVSquareBoundaryMapper.cxx
    vtkSVParameterizeSurfaceOnPolycube.cxx
    vtkSVSphericalMapper.cxx
    vtkSVParameterizeVolumeOnPolycube.cxx
    vtkSVPointSetBoundaryMapper.cxx
    vtkSVPlanarMapper.cxx
    vtkSVSuperSquareBoundaryMapper.cxx
)

vtk_module_add_module(VTK::SVParameterization
    HEADERS ${vtkSVParameterization_HEADERS}
    SOURCES ${vtkSVParameterization_SOURCES}
)
