set(vtkSV3Model_HEADERS
    sv3_ModelElement.h
    sv3_ModelGroup.h
)

set(vtkSV3Model_SOURCES
    sv3_ModelElement.cxx
    sv3_ModelGroup.cxx
)

vtk_module_add_module(VTK::SV3Model
    HEADERS ${vtkSV3Model_HEADERS}
    SOURCES ${vtkSV3Model_SOURCES}
)
