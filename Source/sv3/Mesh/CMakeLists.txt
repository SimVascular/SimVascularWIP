set(vtkSV3Mesh_HEADERS
    sv3_Mesh.h
    sv3_MeshGroup.h
)

set(vtkSV3Mesh_SOURCES
    sv3_Mesh.cxx
    sv3_MeshGroup.cxx
)

vtk_module_add_module(VTK::SV3Mesh
    HEADERS ${vtkSV3Mesh_HEADERS}
    SOURCES ${vtkSV3Mesh_SOURCES}
)
