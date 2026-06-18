set(vtkSVSegmentation_HEADERS
    vtkSVNewVesselNetworkDecomposerAndParameterizer.h
    vtkSVEdgeWeightedCVT.h
    vtkSVPolycubeGenerator.h
    vtkSVCenterlines.h
    vtkSVCenterlinesEdgeWeightedCVT.h
    vtkSVSurfaceCenterlineAttributesPasser.h
    vtkSVCenterlineGraph.h
    vtkSVVesselNetworkDecomposerAndParameterizer.h
    vtkSVEdgeWeightedSmoother.h
    vtkSVCenterlinesBasedNormals.h
    vtkSVCenterlineParallelTransportVectors.h
    vtkSVSurfaceCenterlineGrouper.h
    vtkSVCenterlineMerger.h
    vtkSVSurfaceCuboidPatcher.h
    vtkSVGeneralCVT.h
    vtkSVCenterlineGCell.h
    vtkSVCenterlineBranchSplitter.h
    vtkSVPolyBallLine.h
)

set(vtkSVSegmentation_SOURCES
    vtkSVSurfaceCuboidPatcher.cxx
    vtkSVCenterlineGCell.cxx
    vtkSVCenterlinesEdgeWeightedCVT.cxx
    vtkSVCenterlineBranchSplitter.cxx
    vtkSVPolyBallLine.cxx
    vtkSVSurfaceCenterlineGrouper.cxx
    vtkSVEdgeWeightedSmoother.cxx
    vtkSVCenterlineParallelTransportVectors.cxx
    vtkSVCenterlineGraph.cxx
    vtkSVGeneralCVT.cxx
    vtkSVEdgeWeightedCVT.cxx
    vtkSVCenterlineMerger.cxx
    vtkSVSurfaceCenterlineAttributesPasser.cxx
    vtkSVPolycubeGenerator.cxx
    vtkSVCenterlinesBasedNormals.cxx
    vtkSVNewVesselNetworkDecomposerAndParameterizer.cxx
    vtkSVCenterlines.cxx
    vtkSVVesselNetworkDecomposerAndParameterizer.cxx
)

vtk_module_add_module(VTK::SVSegmentation
    HEADERS ${vtkSVSegmentation_HEADERS}
    SOURCES ${vtkSVSegmentation_SOURCES}
)

vtk_module_include(VTK::SVSegmentation
    PUBLIC
    ${VMTK_INCLUDE_DIRS}
)