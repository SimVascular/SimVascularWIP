set(vtkSV4ImageProcessing_HEADERS
    sv4gui_ImageProcessingUtils.h
)

set(vtkSV4ImageProcessing_SOURCES
    sv4gui_ImageProcessingUtils.cxx
)

vtk_module_add_module(VTK::SV4ImageProcessing
    HEADERS ${vtkSV4ImageProcessing_HEADERS}
    SOURCES ${vtkSV4ImageProcessing_SOURCES}
)