set(vtkSV3Path_HEADERS
    sv3_VtkParametricSpline.h
    sv3_PathGroup.h
    sv3_PathIO.h
    sv3_PathElement.h
    sv3_Spline.h
    sv3_PathUtils.h
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

vtk_module_link(VTK::SV3Path PUBLIC tinyxml2::tinyxml2)  # todo superbuild
