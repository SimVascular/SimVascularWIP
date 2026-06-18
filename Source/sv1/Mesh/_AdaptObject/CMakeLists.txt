set(vtkSV1MeshAdaptObject_HEADERS
    sv_AdaptObject.h
    sv_adapt_utils.h
    sv_eispack.h
    cvSolverIO.h
)

set(vtkSV1MeshAdaptObject_SOURCES
    sv_AdaptObject.cxx
    sv_adapt_utils.cxx
    sv_eispack.cxx
    cvSolverIO.cxx
)

vtk_module_add_module(VTK::SV1MeshAdaptObject
    HEADERS ${vtkSV1MeshAdaptObject_HEADERS}
    SOURCES ${vtkSV1MeshAdaptObject_SOURCES}
)

vtk_module_include(VTK::SV1MeshAdaptObject
    PUBLIC
    ${TETGEN_INCLUDE_DIR}
)