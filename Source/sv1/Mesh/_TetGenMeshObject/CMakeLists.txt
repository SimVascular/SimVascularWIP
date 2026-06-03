set(vtkSV1MeshTetGenMeshObject_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svTetGenMeshObjectExports.h)
set(vtkSV1MeshTetGenMeshObject_HEADERS
    sv_TetGenMeshObject.h
    sv_tetgenmesh_utils.h
    sv_TetGenMeshSystem.h
    ${vtkSV1MeshTetGenMeshObject_EXPORT_HEADER}
)

set(vtkSV1MeshTetGenMeshObject_SOURCES
    sv_TetGenMeshObject.cxx
    sv_tetgenmesh_utils.cxx
    sv_TetGenMeshSystem.cxx
)

vtk_module_add_module(VTK::SV1MeshTetGenMeshObject
    HEADERS ${vtkSV1MeshTetGenMeshObject_HEADERS}
    SOURCES ${vtkSV1MeshTetGenMeshObject_SOURCES}
)
generate_export_header(VTK::SV1MeshTetGenMeshObject
    EXPORT_MACRO_NAME "SV_EXPORT_TETGENMESHOBJECT"
    EXPORT_FILE_NAME ${vtkSV1MeshTetGenMeshObject_EXPORT_HEADER}
)