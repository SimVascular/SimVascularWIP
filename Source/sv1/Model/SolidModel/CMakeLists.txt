set(vtkSV1ModelSolidModel_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svSolidModelExports.h)
set(vtkSV1ModelSolidModel_HEADERS
    sv_SolidModel.h
    ${vtkSV1ModelSolidModel_EXPORT_HEADER}
)

set(vtkSV1ModelSolidModel_SOURCES
    sv_SolidModel.cxx
)

vtk_module_add_module(VTK::SV1ModelSolidModel
    HEADERS ${vtkSV1ModelSolidModel_HEADERS}
    SOURCES ${vtkSV1ModelSolidModel_SOURCES}
)
generate_export_header(VTK::SV1ModelSolidModel
    EXPORT_MACRO_NAME "SV_EXPORT_SOLIDMODEL"
    EXPORT_FILE_NAME ${vtkSV1ModelSolidModel_EXPORT_HEADER}
)