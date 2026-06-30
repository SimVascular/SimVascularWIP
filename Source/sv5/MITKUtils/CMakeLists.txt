set(vtkSV5MITKUtils_HEADERS
    mitkBaseData.h
    mitkTimeGeometry.h
)

set(vtkSV5MITKUtils_SOURCES
    mitkBaseData.cxx
    mitkTimeGeometry.cxx
)

vtk_module_add_module(VTK::SV5MITKUtils
    HEADERS ${vtkSV5MITKUtils_HEADERS}
    SOURCES ${vtkSV5MITKUtils_SOURCES}
)