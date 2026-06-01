set(vtkSV4ProjectManagement_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModuleProjectManagementExports.h)
set(vtkSV4ProjectManagement_HEADERS
    sv4gui_DataNodeOperation.h
    sv4gui_ModelFolder.h
    sv4gui_DataFolder.h
    sv4gui_MultiPhysicsFolder.h
    sv4gui_MeshFolder.h
    sv4gui_PathFolder.h
    sv4gui_ProjectManager.h
    sv4gui_SegmentationFolder.h
    sv4gui_RepositoryFolder.h
    sv4gui_ROMSimulationFolder.h
    sv4gui_DataNodeOperationInterface.h
    sv4gui_SimulationFolder.h
    sv4gui_ProjectFolder.h
    sv4gui_ImageFolder.h
    ${vtkSV4ProjectManagement_EXPORT_HEADER}
)

set(vtkSV4ProjectManagement_SOURCES
    sv4gui_ProjectManager.cxx
    sv4gui_DataNodeOperation.cxx
    sv4gui_RepositoryFolder.cxx
    sv4gui_DataNodeOperationInterface.cxx
    sv4gui_ProjectFolder.cxx
    sv4gui_ROMSimulationFolder.cxx
    sv4gui_PathFolder.cxx
    sv4gui_ModelFolder.cxx
    sv4gui_MultiPhysicsFolder.cxx
    sv4gui_ImageFolder.cxx
    sv4gui_SegmentationFolder.cxx
    sv4gui_DataFolder.cxx
    sv4gui_MeshFolder.cxx
    sv4gui_SimulationFolder.cxx
)

vtk_module_add_module(VTK::SV4ProjectManagement
    HEADERS ${vtkSV4ProjectManagement_HEADERS}
    SOURCES ${vtkSV4ProjectManagement_SOURCES}
)
generate_export_header(VTK::SV4ProjectManagement
    BASE_NAME "SV4GUIMODULEPROJECTMANAGEMENT"
    EXPORT_FILE_NAME ${vtkSV4ProjectManagement_EXPORT_HEADER}
)