option(VTKSV_PREDELAUNAY_SPLIT "Split cells manually before giving to delaunay" ON)
mark_as_advanced(VTKSV_PREDELAUNAY_SPLIT)
set(VTKSV_DELAUNAY_TYPE "OLD" CACHE STRING "Options are CURRENT, OLD, TRIANGLE")
set_property(CACHE VTKSV_DELAUNAY_TYPE PROPERTY STRINGS CURRENT OLD TRIANGLE)
mark_as_advanced(VTKSV_DELAUNAY_TYPE)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/delaunay_options.h.in" "${CMAKE_CURRENT_BINARY_DIR}/delaunay_options.h")

set(vtkSVBoolean_HEADERS
    vtkSVMultiplePolyDataIntersectionFilter.h
    vtkSVLoopIntersectionPolyDataFilter.h
    vtkSVLoopBooleanPolyDataFilter.h
    "${CMAKE_CURRENT_BINARY_DIR}/delaunay_options.h"
)

set(vtkSVBoolean_SOURCES
    vtkSVMultiplePolyDataIntersectionFilter.cxx
    vtkSVLoopBooleanPolyDataFilter.cxx
    vtkSVLoopIntersectionPolyDataFilter.cxx
)

if("${VTKSV_DELAUNAY_TYPE}" STREQUAL "OLD")
    list(APPEND vtkSVBoolean_HEADERS vtkDelaunay2D_60.h)
    list(APPEND vtkSVBoolean_SOURCES vtkDelaunay2D_60.cxx)
endif()

vtk_module_add_module(VTK::SVBoolean
    HEADERS ${vtkSVBoolean_HEADERS}
    SOURCES ${vtkSVBoolean_SOURCES}
)
