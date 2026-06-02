set(vtkSV4MeshCommon_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svCommonExports.h)
set(vtkSV4MeshCommon_HEADERS
    sv4gui_MeshTetGenAdaptor.h
    sv4gui_MitkMeshIO.h
    sv4gui_MitkMesh.h
    sv4gui_MeshTetGen.h
    sv4gui_MitkMeshObjectFactory.h
    sv4gui_RegisterTetGenFunction.h
    sv4gui_MitkMeshMapper2D.h
    sv4gui_MeshFactory.h
    sv4gui_MeshLegacyIO.h
    sv4gui_Mesh.h
    sv4gui_MeshAdaptor.h
    sv4gui_MitkMeshMapper3D.h
    sv4gui_MitkMeshOperation.h
    ${vtkSV4MeshCommon_EXPORT_HEADER}
)

set(vtkSV4MeshCommon_SOURCES
    sv4gui_MeshTetGenAdaptor.cxx
    sv4gui_Mesh.cxx
    sv4gui_MeshFactory.cxx
    sv4gui_MitkMeshIO.cxx
    sv4gui_MitkMeshMapper2D.cxx
    sv4gui_MeshAdaptor.cxx
    sv4gui_MitkMeshMapper3D.cxx
    sv4gui_MeshLegacyIO.cxx
    sv4gui_MeshTetGen.cxx
    sv4gui_MitkMesh.cxx
    sv4gui_MitkMeshObjectFactory.cxx
    sv4gui_MitkMeshOperation.cxx
    sv4gui_RegisterTetGenFunction.cxx
)

vtk_module_add_module(VTK::SV4MeshCommon
    HEADERS ${vtkSV4MeshCommon_HEADERS}
    SOURCES ${vtkSV4MeshCommon_SOURCES}
)
generate_export_header(VTK::SV4MeshCommon
    EXPORT_MACRO_NAME "SV_EXPORT_COMMON"
    EXPORT_FILE_NAME ${vtkSV4MeshCommon_EXPORT_HEADER}
)