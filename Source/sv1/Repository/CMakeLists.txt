set(vtkSV1Repository_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svRepositoryExports.h)
set(vtkSV1Repository_HEADERS
    sv_DataSet.h
    sv_RepositoryData.h
    sv_StrPts.h
    sv_UnstructuredGrid.h
    sv_DataObject.h
    sv_PolyData.h
    ${vtkSV1Repository_EXPORT_HEADER}
)

set(vtkSV1Repository_SOURCES
    sv_RepositoryData.cxx
    sv_UnstructuredGrid.cxx
    sv_PolyData.cxx
    sv_DataObject.cxx
    sv_StrPts.cxx
    sv_DataSet.cxx
)

vtk_module_add_module(VTK::SV1Repository
    HEADERS ${vtkSV1Repository_HEADERS}
    SOURCES ${vtkSV1Repository_SOURCES}
)
generate_export_header(VTK::SV1Repository
    EXPORT_MACRO_NAME "SV_EXPORT_REPOSITORY"
    EXPORT_FILE_NAME ${vtkSV1Repository_EXPORT_HEADER}
)