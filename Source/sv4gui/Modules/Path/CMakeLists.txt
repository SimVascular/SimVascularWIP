set(vtkSV4Path_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svPathExports.h)
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
    EXPORT_MACRO_NAME "SV_EXPORT_PATH"
    EXPORT_FILE_NAME ${vtkSV4Path_EXPORT_HEADER}
)