set(vtkSVCommon_HEADERS
    vtkSVGlobals.h
    vtkSVGeneralUtils.h
    vtkSVRenderer.h
    vtkSVMathUtils.h
    vtkSVSparseMatrix.h
)

set(vtkSVCommon_SOURCES
    vtkSVSparseMatrix.cxx
    vtkSVMathUtils.cxx
    vtkSVGeneralUtils.cxx
    vtkSVRenderer.cxx
)

vtk_module_add_module(VTK::SVCommon
    HEADERS ${vtkSVCommon_HEADERS}
    NOWRAP_HEADERS vtkSVIdFilter.h
    SOURCES ${vtkSVCommon_SOURCES}
)
