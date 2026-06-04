set(vtkSV4MachineLearning_HEADERS
    sv4gui_MachineLearningUtils.h
    sv4gui_json.hxx
)

set(vtkSV4MachineLearning_SOURCES
    sv4gui_MachineLearningUtils.cxx
)

vtk_module_add_module(VTK::SV4MachineLearning
    HEADERS ${vtkSV4MachineLearning_HEADERS}
    SOURCES ${vtkSV4MachineLearning_SOURCES}
)

vtk_module_link(VTK::SV4MachineLearning PUBLIC ${QT_LIBRARIES} Python::Module)