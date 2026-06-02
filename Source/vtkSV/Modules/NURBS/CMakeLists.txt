set(vtkSVNURBS_HEADERS
    vtkSVNURBSUtils.h
    vtkSVLoftNURBSSurface.h
    vtkSVControlGrid.h
    vtkSVNURBSObject.h
    vtkSVNURBSSurface.h
    vtkSVMUPFESNURBSWriter.h
    vtkSVPERIGEENURBSCollectionWriter.h
    vtkSVNURBSVolume.h
    vtkSVPERIGEENURBSWriter.h
    vtkSVNURBSCurve.h
    vtkSVLoftNURBSVolume.h
    vtkSVLoftNURBSCurve.h
    vtkSVNURBSCollection.h
)

set(vtkSVNURBS_SOURCES
    vtkSVNURBSCollection.cxx
    vtkSVControlGrid.cxx
    vtkSVMUPFESNURBSWriter.cxx
    vtkSVLoftNURBSVolume.cxx
    vtkSVNURBSSurface.cxx
    vtkSVLoftNURBSCurve.cxx
    vtkSVNURBSUtils.cxx
    vtkSVLoftNURBSSurface.cxx
    vtkSVNURBSObject.cxx
    vtkSVNURBSVolume.cxx
    vtkSVPERIGEENURBSCollectionWriter.cxx
    vtkSVNURBSCurve.cxx
    vtkSVPERIGEENURBSWriter.cxx
)

vtk_module_add_module(VTK::SVNURBS
    HEADERS ${vtkSVNURBS_HEADERS}
    SOURCES ${vtkSVNURBS_SOURCES}
)
