set(vtkSV1ModelOCCTSolidModel_HEADERS
    sv_occtsolid_utils.h
    sv_OCCTSolidModel.h
)

set(vtkSV1ModelOCCTSolidModel_SOURCES
    sv_occtsolid_utils.cxx
    sv_OCCTSolidModel.cxx
)

vtk_module_add_module(VTK::SV1ModelOCCTSolidModel
    HEADERS ${vtkSV1ModelOCCTSolidModel_HEADERS}
    SOURCES ${vtkSV1ModelOCCTSolidModel_SOURCES}
)

vtk_module_include(VTK::SV1ModelOCCTSolidModel
    PUBLIC
    ${OpenCASCADE_INCLUDE_DIR}
)

vtk_module_link(VTK::SV1ModelOCCTSolidModel PUBLIC ${OpenCASCADE_LIBRARIES})