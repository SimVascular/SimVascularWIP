set(vtkSV1MeshAdaptObject_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svAdaptObjectExports.h)
set(vtkSV1MeshAdaptObject_HEADERS
    sv_AdaptObject.h
    sv_adapt_utils.h
    sv_eispack.h
    ${vtkSV1MeshAdaptObject_EXPORT_HEADER}
)

set(vtkSV1MeshAdaptObject_SOURCES
    sv_AdaptObject.cxx
    sv_adapt_utils.cxx
    sv_eispack.cxx
)

vtk_module_add_module(VTK::SV1MeshAdaptObject
    HEADERS ${vtkSV1MeshAdaptObject_HEADERS}
    SOURCES ${vtkSV1MeshAdaptObject_SOURCES}
)
generate_export_header(VTK::SV1MeshAdaptObject
    EXPORT_MACRO_NAME "SV_EXPORT_ADAPTOBJECT"
    EXPORT_FILE_NAME ${vtkSV1MeshAdaptObject_EXPORT_HEADER}
)