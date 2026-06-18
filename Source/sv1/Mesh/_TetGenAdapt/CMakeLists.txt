set(vtkSV1MeshTetGenAdapt_HEADERS
    sv_TetGenAdapt.h
)

set(vtkSV1MeshTetGenAdapt_SOURCES
    sv_TetGenAdapt.cxx
)

vtk_module_add_module(VTK::SV1MeshTetGenAdapt
    HEADERS ${vtkSV1MeshTetGenAdapt_HEADERS}
    SOURCES ${vtkSV1MeshTetGenAdapt_SOURCES}
)