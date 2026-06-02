set(vtkSVBoolean_HEADERS
    vtkDelaunay2D_60.h
    vtkSVMultiplePolyDataIntersectionFilter.h
    vtkSVLoopIntersectionPolyDataFilter.h
    vtkSVLoopBooleanPolyDataFilter.h
)

set(vtkSVBoolean_SOURCES
    vtkSVMultiplePolyDataIntersectionFilter.cxx
    vtkSVLoopBooleanPolyDataFilter.cxx
    vtkDelaunay2D_60.cxx
    vtkSVLoopIntersectionPolyDataFilter.cxx
)

vtk_module_add_module(VTK::SVBoolean
    HEADERS ${vtkSVBoolean_HEADERS}
    SOURCES ${vtkSVBoolean_SOURCES}
)
