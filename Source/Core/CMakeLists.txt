set(vtkSV1Repository_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svRepositoryExports.h)
set(vtkSV1Utils_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svUtilsExports.h)

configure_file(simvascular_version.h.in "${CMAKE_CURRENT_BINARY_DIR}/simvascular_version.h")
configure_file(simvascular_options.h.in "${CMAKE_CURRENT_BINARY_DIR}/simvascular_options.h")

set(vtkSVInclude_HEADERS
        SimVascular.h
        sv_Math.h
        sv_PolyData.h
        sv_vtk_utils.h
        "${CMAKE_CURRENT_BINARY_DIR}/simvascular_version.h"
        "${CMAKE_CURRENT_BINARY_DIR}/simvascular_options.h"
        ${vtkSV1Repository_EXPORT_HEADER}
        ${vtkSV1Utils_EXPORT_HEADER}
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
generate_export_header(VTK::SVCore
        EXPORT_MACRO_NAME "SV_EXPORT_REPOSITORY"
        EXPORT_FILE_NAME ${vtkSV1Repository_EXPORT_HEADER}
)
generate_export_header(VTK::SVCore
        EXPORT_MACRO_NAME "SV_EXPORT_UTILS"
        EXPORT_FILE_NAME ${vtkSV1Utils_EXPORT_HEADER}
)
