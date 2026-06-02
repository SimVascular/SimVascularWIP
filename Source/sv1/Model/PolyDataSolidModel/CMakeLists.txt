set(vtkSV1ModelPolyDataSolidModel_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svPolyDataSolidModelExports.h)
set(vtkSV1ModelPolyDataSolidModel_HEADERS
    sv_vtkGetBoundaryFaces.h
    sv_polydatasolid_utils.h
    sv_PolyDataSolid.h
    ${vtkSV1ModelPolyDataSolidModel_EXPORT_HEADER}
)

set(vtkSV1ModelPolyDataSolidModel_SOURCES
    sv_PolyDataSolid.cxx
    sv_polydatasolid_utils.cxx
    sv_vtkGetBoundaryFaces.cxx
)

vtk_module_add_module(VTK::SV1ModelPolyDataSolidModel
    HEADERS ${vtkSV1ModelPolyDataSolidModel_HEADERS}
    SOURCES ${vtkSV1ModelPolyDataSolidModel_SOURCES}
)
generate_export_header(VTK::SV1ModelPolyDataSolidModel
    EXPORT_MACRO_NAME "SV_EXPORT_POLYDATASOLIDMODEL"
    EXPORT_FILE_NAME ${vtkSV1ModelPolyDataSolidModel_EXPORT_HEADER}
)