set(vtkSV4MachineLearning_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svMachineLearningExports.h)
set(vtkSV4MachineLearning_HEADERS
    sv4gui_MachineLearningUtils.h
    sv4gui_json.hxx
    ${vtkSV4MachineLearning_EXPORT_HEADER}
)

set(vtkSV4MachineLearning_SOURCES
    sv4gui_MachineLearningUtils.cxx
)

vtk_module_add_module(VTK::SV4MachineLearning
    HEADERS ${vtkSV4MachineLearning_HEADERS}
    SOURCES ${vtkSV4MachineLearning_SOURCES}
)
generate_export_header(VTK::SV4MachineLearning
    EXPORT_MACRO_NAME "SV_EXPORT_MACHINELEARNING"
    EXPORT_FILE_NAME ${vtkSV4MachineLearning_EXPORT_HEADER}
)