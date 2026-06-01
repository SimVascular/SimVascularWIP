set(vtkSV4Path_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModulePathExports.h)
set(vtkSV4Path_HEADERS
    sv4gui_PathElement.h
    sv4gui_Path.h
    sv4gui_PathObjectFactory.h
    sv4gui_PathVtkMapper3D.h
    sv4gui_PathLegacyIO.h
    sv4gui_PathVtkMapper2D.h
    sv4gui_PathOperation.h
    sv4gui_PathIO.h
    sv4gui_PathDataInteractor.h
    ${vtkSV4Path_EXPORT_HEADER}
)

set(vtkSV4Path_SOURCES
    sv4gui_PathIO.cxx
    sv4gui_PathVtkMapper2D.cxx
    sv4gui_PathObjectFactory.cxx
    sv4gui_PathLegacyIO.cxx
    sv4gui_PathDataInteractor.cxx
    sv4gui_Path.cxx
    sv4gui_PathVtkMapper3D.cxx
    sv4gui_PathElement.cxx
    sv4gui_PathOperation.cxx
)

vtk_module_add_module(VTK::SV4Path
    HEADERS ${vtkSV4Path_HEADERS}
    SOURCES ${vtkSV4Path_SOURCES}
)
generate_export_header(VTK::SV4Path
    BASE_NAME "SV4GUIMODULEPATH"
    EXPORT_FILE_NAME ${vtkSV4Path_EXPORT_HEADER}
)
vtk_module_link(VTK::SV4Path PUBLIC Qt6::Core ${MITK_LIBRARIES})

# TODO this is a hack. I'm not sure how this is actually supposed to be initialized.
vtk_module_definitions(VTK::SV4Path PUBLIC US_MODULE_NAME='SV4Path')

# TODO declare qt resources