configure_file(simvascular_version.h.in "${CMAKE_CURRENT_BINARY_DIR}/simvascular_version.h")
configure_file(simvascular_options.h.in "${CMAKE_CURRENT_BINARY_DIR}/simvascular_options.h")

set(vtkSVInclude_HEADERS
        SimVascular.h
        sv_Math.h
        sv_PolyData.h
        sv_vtk_utils.h
        "${CMAKE_CURRENT_BINARY_DIR}/simvascular_version.h"
        "${CMAKE_CURRENT_BINARY_DIR}/simvascular_options.h"
)

set(vtkSVInclude_SOURCES
        sv_Math.cxx
        sv_PolyData.cxx
        sv_vtk_utils.cxx
)

vtk_module_add_module(VTK::SVCore
        HEADERS ${vtkSVInclude_HEADERS}
        SOURCES ${vtkSVInclude_SOURCES}
)
