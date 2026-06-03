set(vtkSV1MeshTetGenAdapt_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svTetGenAdaptExports.h)
set(vtkSV1MeshTetGenAdapt_HEADERS
    sv_TetGenAdapt.h
    ${vtkSV1MeshTetGenAdapt_EXPORT_HEADER}
)

set(vtkSV1MeshTetGenAdapt_SOURCES
    sv_TetGenAdapt.cxx
)

vtk_module_add_module(VTK::SV1MeshTetGenAdapt
    HEADERS ${vtkSV1MeshTetGenAdapt_HEADERS}
    SOURCES ${vtkSV1MeshTetGenAdapt_SOURCES}
)
generate_export_header(VTK::SV1MeshTetGenAdapt
    EXPORT_MACRO_NAME "SV_EXPORT_TETGENADAPT"
    EXPORT_FILE_NAME ${vtkSV1MeshTetGenAdapt_EXPORT_HEADER}
)