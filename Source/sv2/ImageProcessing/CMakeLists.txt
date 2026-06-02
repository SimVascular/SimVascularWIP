set(vtkSV2ImageProcessing_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svImageProcessingExports.h)
set(vtkSV2ImageProcessing_HEADERS
    sv2_DistanceMap.h
    sv2_image.h
    sv2_read_header.h
    sv2_decode.h
    sv2_img_offsets.h
    sv2_calc_correction_eqn.h
    sv2_img_threshold.h
    sv2_mask_image_in_place.h
    ${vtkSV2ImageProcessing_EXPORT_HEADER}
)

set(vtkSV2ImageProcessing_SOURCES
    sv2_img_threshold.cxx
    sv2_calc_correction_eqn.cxx
    sv2_image.cxx
    sv2_mask_image_in_place.cxx
    sv2_DistanceMap.cxx
    sv2_read_header.cxx
    sv2_decode.cxx
)

vtk_module_add_module(VTK::SV2ImageProcessing
    HEADERS ${vtkSV2ImageProcessing_HEADERS}
    SOURCES ${vtkSV2ImageProcessing_SOURCES}
)
generate_export_header(VTK::SV2ImageProcessing
    EXPORT_MACRO_NAME "SV_EXPORT_IMAGEPROCESSING"
    EXPORT_FILE_NAME ${vtkSV2ImageProcessing_EXPORT_HEADER}
)