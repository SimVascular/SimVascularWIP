set(vtkSV1ModelOCCTSolidModel_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svOCCTSolidModelExports.h)
set(vtkSV1ModelOCCTSolidModel_HEADERS
    sv_occtsolid_utils.h
    sv_OCCTSolidModel.h
    ${vtkSV1ModelOCCTSolidModel_EXPORT_HEADER}
)

set(vtkSV1ModelOCCTSolidModel_SOURCES
    sv_occtsolid_utils.cxx
    sv_OCCTSolidModel.cxx
)

vtk_module_add_module(VTK::SV1ModelOCCTSolidModel
    HEADERS ${vtkSV1ModelOCCTSolidModel_HEADERS}
    SOURCES ${vtkSV1ModelOCCTSolidModel_SOURCES}
)
generate_export_header(VTK::SV1ModelOCCTSolidModel
    EXPORT_MACRO_NAME "SV_EXPORT_OCCTSOLIDMODEL"
    EXPORT_FILE_NAME ${vtkSV1ModelOCCTSolidModel_EXPORT_HEADER}
)