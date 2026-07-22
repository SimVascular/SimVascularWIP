set(vtkSV1MeshMMGMeshUtils_HEADERS
    sv_mmg_mesh_utils.h
)

set(vtkSV1MeshMMGMeshUtils_SOURCES
    sv_mmg_mesh_utils.cxx
)

vtk_module_add_module(VTK::SV1MeshMMGMeshUtils
    HEADERS ${vtkSV1MeshMMGMeshUtils_HEADERS}
    SOURCES ${vtkSV1MeshMMGMeshUtils_SOURCES}
)

vtk_module_include(VTK::SV1MeshMMGMeshUtils
    PUBLIC
    ${MMG_INCLUDE_DIR}
)

get_filename_component(MMG_LIB_DIR "${MMG_INCLUDE_DIR}/../lib" ABSOLUTE)
vtk_module_link(VTK::SV1MeshMMGMeshUtils PUBLIC
    ${MMG_LIB_DIR}/libmmgs.a
    ${MMG_LIB_DIR}/libmmg.a
)