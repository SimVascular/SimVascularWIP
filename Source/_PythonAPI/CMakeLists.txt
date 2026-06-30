set(vtkSVPythonAPI_HEADERS
    Imaging_PyModule.h
    Segmentation_PyModule.h
    # Geometry_PyModule.h
    Math_PyModule.h
    # Meshing_PyModule.h
    MeshUtils_PyModule.h
    PathPlanning_PyModule.h
    PyUtils.h
    # Modeling_PyModule.h
    # Simulation_PyModule.h
    Vmtk_PyModule.h
)

set(vtkSVPythonAPI_SOURCES
    Imaging_PyModule.cxx
    Segmentation_PyModule.cxx
    # Geometry_PyModule.cxx
    Math_PyModule.cxx
    # Meshing_PyModule.cxx
    MeshUtils_PyModule.cxx
    PathPlanning_PyModule.cxx
    PyUtils.cxx
    # Modeling_PyModule.cxx
    # Simulation_PyModule.cxx
    Vmtk_PyModule.cxx
)

vtk_module_add_module(VTK::SVPythonAPI
    HEADERS ${vtkSVPythonAPI_HEADERS}
    SOURCES ${vtkSVPythonAPI_SOURCES}
)

vtk_module_include(VTK::SVPythonAPI
    PUBLIC
    ${Python3_INCLUDE_DIRS}
)