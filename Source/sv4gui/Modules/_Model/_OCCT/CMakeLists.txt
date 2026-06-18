set(vtkSV4ModelOCCT_HEADERS
    sv4gui_ModelUtilsOCCT.h
    sv4gui_RegisterOCCTFunction.h
    sv4gui_ModelElementOCCT.h
)

set(vtkSV4ModelOCCT_SOURCES
    sv4gui_ModelElementOCCT.cxx
    sv4gui_ModelUtilsOCCT.cxx
    sv4gui_RegisterOCCTFunction.cxx
)

vtk_module_add_module(VTK::SV4ModelOCCT
    HEADERS ${vtkSV4ModelOCCT_HEADERS}
    SOURCES ${vtkSV4ModelOCCT_SOURCES}
)