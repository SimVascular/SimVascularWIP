set(vtkSV1MeshMeshUtils_HEADERS
    sv_vmtk_utils.h
    sv_tetgenmesh_utils.h
)

set(vtkSV1MeshMeshUtils_SOURCES
    sv_vmtk_utils.cxx
    sv_tetgenmesh_utils.cxx
)

vtk_module_add_module(VTK::SV1MeshMeshUtils
    HEADERS ${vtkSV1MeshMeshUtils_HEADERS}
    SOURCES ${vtkSV1MeshMeshUtils_SOURCES}
)

vtk_module_include(VTK::SV1MeshMeshUtils
    PUBLIC
    ${TETGEN_INCLUDE_DIR}
    ${VMTK_INCLUDE_DIRS}
)

vtk_module_link(VTK::SV1MeshMeshUtils PUBLIC
    vtkvmtkCommon
    vtkvmtkComputationalGeometry
    vtkvmtkDifferentialGeometry
    vtkvmtkIO
    vtkvmtkMisc
    vtkvmtkSegmentation
    ${TETGEN_LIBRARY}
)