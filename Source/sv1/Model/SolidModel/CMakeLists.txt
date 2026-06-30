set(vtkSV1ModelSolidModel_HEADERS
    sv_SolidModel.h
)

set(vtkSV1ModelSolidModel_SOURCES
    sv_SolidModel.cxx
)

vtk_module_add_module(VTK::SV1ModelSolidModel
    HEADERS ${vtkSV1ModelSolidModel_HEADERS}
    SOURCES ${vtkSV1ModelSolidModel_SOURCES}
)