configure_file(simvascular_version.h.in "${CMAKE_CURRENT_BINARY_DIR}/simvascular_version.h")
configure_file(simvascular_options.h.in "${CMAKE_CURRENT_BINARY_DIR}/simvascular_options.h")

set(vtkSVInclude_HEADERS
    sv_VTK.h
    sv_IOstream.h
    SimVascular_python.h
    SimVascular.h
    "${CMAKE_CURRENT_BINARY_DIR}/simvascular_version.h"
    "${CMAKE_CURRENT_BINARY_DIR}/simvascular_options.h"
)

set(vtkSVInclude_SOURCES
    
)

vtk_module_add_module(VTK::SVInclude
    HEADERS ${vtkSVInclude_HEADERS}
    SOURCES ${vtkSVInclude_SOURCES}
    HEADER_ONLY
)