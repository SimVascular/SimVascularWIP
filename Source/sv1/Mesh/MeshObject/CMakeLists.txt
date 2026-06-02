set(vtkSV1MeshMeshObject_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svMeshObjectExports.h)
set(vtkSV1MeshMeshObject_HEADERS
    sv_MeshSystem.h
    sv_MeshObject.h
    ${vtkSV1MeshMeshObject_EXPORT_HEADER}
)

set(vtkSV1MeshMeshObject_SOURCES
    sv_MeshObject.cxx
    sv_MeshSystem.cxx
)

vtk_module_add_module(VTK::SV1MeshMeshObject
    HEADERS ${vtkSV1MeshMeshObject_HEADERS}
    SOURCES ${vtkSV1MeshMeshObject_SOURCES}
)
generate_export_header(VTK::SV1MeshMeshObject
    EXPORT_MACRO_NAME "SV_EXPORT_MESHOBJECT"
    EXPORT_FILE_NAME ${vtkSV1MeshMeshObject_EXPORT_HEADER}
)