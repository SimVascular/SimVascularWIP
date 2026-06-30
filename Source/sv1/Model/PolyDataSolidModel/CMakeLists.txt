set(vtkSV1ModelPolyDataSolidModel_HEADERS
    sv_vtkGetBoundaryFaces.h
    sv_polydatasolid_utils.h
    sv_PolyDataSolid.h
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