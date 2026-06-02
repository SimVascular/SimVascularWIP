set(vtkSVInclude_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svIncludeExports.h)
set(vtkSVInclude_HEADERS
    sv_VTK.h
    sv_IOstream.h
    SimVascular_python.h
    SimVascular.h
    ${vtkSVInclude_EXPORT_HEADER}
)

set(vtkSVInclude_SOURCES
    
)

vtk_module_add_module(VTK::SVInclude
    HEADERS ${vtkSVInclude_HEADERS}
    SOURCES ${vtkSVInclude_SOURCES}
    HEADER_ONLY
)
generate_export_header(VTK::SVInclude
    EXPORT_MACRO_NAME "SV_EXPORT_INCLUDE"
    EXPORT_FILE_NAME ${vtkSVInclude_EXPORT_HEADER}
)