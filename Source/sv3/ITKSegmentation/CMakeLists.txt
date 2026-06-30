set(vtkSV3ITKSegmentation_HEADERS
    sv3_ITKLevelSet.h
    sv3_VascularPhaseTwoLevelSetFunction.h
    sv3_VascularLevelSetFunction.h
    sv3_ITKLset_ExtraUtils.h
    sv3_ITKLSet_PYTHON_Macros.h
    sv3_VascularPhaseOneLevelSetFunction.h
    sv3_VascularLevelSetImageFilter.h
    sv3_ITKLset_ITK_Macros.h
    sv3_VascularPhaseOneLevelSetImageFilter.h
    sv3_ITKLset_ITKUtils.h
    sv3_ITKLset_ConnectVTKITK.h
    sv3_ITKLevelSetBase.h
    sv3_ITKLset_ImgInfo.h
    sv3_ITKLset_Macros.h
    sv3_ITKLset_VTK_Macros.h
    sv3_ITKLset_EdgeRemapImageFilter.h
    sv3_VascularLevelSetObserver.h
    sv3_GeodesicActiveContourLaplacianSmoothLevelSetImageFilter.h
    sv3_VascularPhaseTwoLevelSetImageFilter.h
    sv3_VascularPhaseTwoLevelSetFunction.hxx
    sv3_ITKLset_ITKUtils.hxx
    sv3_VascularPhaseOneLevelSetFunction.hxx
    sv3_VascularPhaseOneLevelSetImageFilter.hxx
    sv3_VascularLevelSetFunction.hxx
    sv3_VascularPhaseTwoLevelSetImageFilter.hxx
)

set(vtkSV3ITKSegmentation_SOURCES
    sv3_ITKUtils.cxx
    sv3_ITKLset_ExtraUtils.cxx
    sv3_ITKLevelSet.cxx
)

vtk_module_add_module(VTK::SV3ITKSegmentation
    HEADERS ${vtkSV3ITKSegmentation_HEADERS}
    SOURCES ${vtkSV3ITKSegmentation_SOURCES}
)

vtk_module_link(VTK::SV3ITKSegmentation PUBLIC ITKCommon ITKVTK)