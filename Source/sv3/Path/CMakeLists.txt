set(vtkSV3Path_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svPathExports.h)
set(vtkSV3Path_HEADERS
    sv3_VtkParametricSpline.h
    sv3_PathGroup.h
    sv3_PathIO.h
    sv3_PathElement.h
    sv3_Spline.h
    sv3_PathUtils.h
    ${vtkSV3Path_EXPORT_HEADER}
)

set(vtkSV3Path_SOURCES
    sv3_Spline.cxx
    sv3_VtkParametricSpline.cxx
    sv3_PathIO.cxx
    sv3_PathElement.cxx
    sv3_PathGroup.cxx
    sv3_PathUtils.cxx
)

vtk_module_add_module(VTK::SV3Path
    HEADERS ${vtkSV3Path_HEADERS}
    SOURCES ${vtkSV3Path_SOURCES}
)
generate_export_header(VTK::SV3Path
    EXPORT_MACRO_NAME "SV_EXPORT_PATH"
    EXPORT_FILE_NAME ${vtkSV3Path_EXPORT_HEADER}
)