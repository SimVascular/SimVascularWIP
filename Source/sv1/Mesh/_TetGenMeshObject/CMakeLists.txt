set(vtkSV1MeshTetGenMeshObject_HEADERS
    sv_TetGenMeshObject.h
    sv_TetGenMeshSystem.h
)

set(vtkSV1MeshTetGenMeshObject_SOURCES
    sv_TetGenMeshObject.cxx
    sv_TetGenMeshSystem.cxx
)

vtk_module_add_module(VTK::SV1MeshTetGenMeshObject
    HEADERS ${vtkSV1MeshTetGenMeshObject_HEADERS}
    SOURCES ${vtkSV1MeshTetGenMeshObject_SOURCES}
)
vtk_module_include(VTK::SV1MeshTetGenMeshObject
    PUBLIC
    ${TETGEN_INCLUDE_DIR}
    ${VMTK_INCLUDE_DIRS}
)
