set(vtkSVGeometry_HEADERS
    vtkSVLocalQuadricDecimation.h
    vtkSVLocalApproximatingSubdivisionFilter.h
    vtkSVConstrainedBlend.h
    vtkSVLocalLinearSubdivisionFilter.h
    vtkSVConstrainedSmoothing.h
    vtkSVLocalButterflySubdivisionFilter.h
    vtkSVSmoothVolume.h
    vtkSVLocalSmoothPolyDataFilter.h
    vtkSVLocalLoopSubdivisionFilter.h
    vtkSVUpdeSmoothing.h
    vtkSVLocalInterpolatingSubdivisionFilter.h
)

set(vtkSVGeometry_SOURCES
    vtkSVLocalApproximatingSubdivisionFilter.cxx
    vtkSVLocalLoopSubdivisionFilter.cxx
    vtkSVLocalLinearSubdivisionFilter.cxx
    vtkSVUpdeSmoothing.cxx
    vtkSVSmoothVolume.cxx
    vtkSVConstrainedBlend.cxx
    vtkSVLocalSmoothPolyDataFilter.cxx
    vtkSVLocalButterflySubdivisionFilter.cxx
    vtkSVLocalInterpolatingSubdivisionFilter.cxx
    vtkSVLocalQuadricDecimation.cxx
    vtkSVConstrainedSmoothing.cxx
)

vtk_module_add_module(VTK::SVGeometry
    HEADERS ${vtkSVGeometry_HEADERS}
    SOURCES ${vtkSVGeometry_SOURCES}
)
