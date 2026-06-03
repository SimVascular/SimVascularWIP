set(vtkSV1MeshVMTKUtils_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svVMTKUtilsExports.h)
set(vtkSV1MeshVMTKUtils_HEADERS
    sv_vmtk_utils.h
    ${vtkSV1MeshVMTKUtils_EXPORT_HEADER}
)

set(vtkSV1MeshVMTKUtils_SOURCES
    sv_vmtk_utils.cxx
)

vtk_module_add_module(VTK::SV1MeshVMTKUtils
    HEADERS ${vtkSV1MeshVMTKUtils_HEADERS}
    SOURCES ${vtkSV1MeshVMTKUtils_SOURCES}
)
generate_export_header(VTK::SV1MeshVMTKUtils
    EXPORT_MACRO_NAME "SV_EXPORT_VMTKUTILS"
    EXPORT_FILE_NAME ${vtkSV1MeshVMTKUtils_EXPORT_HEADER}
)