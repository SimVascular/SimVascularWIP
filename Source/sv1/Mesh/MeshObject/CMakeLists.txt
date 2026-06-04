set(vtkSV1MeshMeshObject_HEADERS
    sv_MeshSystem.h
    sv_MeshObject.h
)

set(vtkSV1MeshMeshObject_SOURCES
    sv_MeshObject.cxx
    sv_MeshSystem.cxx
)

vtk_module_add_module(VTK::SV1MeshMeshObject
    HEADERS ${vtkSV1MeshMeshObject_HEADERS}
    SOURCES ${vtkSV1MeshMeshObject_SOURCES}
)