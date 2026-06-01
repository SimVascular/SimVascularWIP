set(vtkSV2PostProcessing_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svPostExports.h)
set(vtkSV2PostProcessing_HEADERS
    sv2_ConvertVisFiles.h
    sv2_CalculateWallShearStress.h
    sv2_CalculateTKE.h
    ${vtkSV2PostProcessing_EXPORT_HEADER}
)

set(vtkSV2PostProcessing_SOURCES
    sv2_CalculateTKE.cxx
    sv2_CalculateWallShearStress.cxx
    sv2_ConvertVisFiles.cxx
)

vtk_module_add_module(VTK::SV2PostProcessing
    HEADERS ${vtkSV2PostProcessing_HEADERS}
    SOURCES ${vtkSV2PostProcessing_SOURCES}
)
generate_export_header(VTK::SV2PostProcessing
    EXPORT_MACRO_NAME "SV_EXPORT_POST"
    EXPORT_FILE_NAME ${vtkSV2PostProcessing_EXPORT_HEADER}
)