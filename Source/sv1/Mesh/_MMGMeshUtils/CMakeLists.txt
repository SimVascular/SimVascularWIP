set(vtkSV1MeshMMGMeshUtils_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svMMGMeshUtilsExports.h)
set(vtkSV1MeshMMGMeshUtils_HEADERS
    sv_mmg_mesh_utils.h
    ${vtkSV1MeshMMGMeshUtils_EXPORT_HEADER}
)

set(vtkSV1MeshMMGMeshUtils_SOURCES
    sv_mmg_mesh_utils.cxx
)

vtk_module_add_module(VTK::SV1MeshMMGMeshUtils
    HEADERS ${vtkSV1MeshMMGMeshUtils_HEADERS}
    SOURCES ${vtkSV1MeshMMGMeshUtils_SOURCES}
)
generate_export_header(VTK::SV1MeshMMGMeshUtils
    EXPORT_MACRO_NAME "SV_EXPORT_MMGMESHUTILS"
    EXPORT_FILE_NAME ${vtkSV1MeshMMGMeshUtils_EXPORT_HEADER}
)