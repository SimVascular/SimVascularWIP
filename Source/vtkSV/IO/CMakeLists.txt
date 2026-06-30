set(vtkSVIO_HEADERS
    vtkSVUnstructuredGridRawReader.h
    vtkSVRawWriter.h
    vtkSVIOUtils.h
    vtkSVPolyDataRawReader.h
)

set(vtkSVIO_SOURCES
    vtkSVRawWriter.cxx
    vtkSVUnstructuredGridRawReader.cxx
    vtkSVIOUtils.cxx
    vtkSVPolyDataRawReader.cxx
)

vtk_module_add_module(VTK::SVIO
    HEADERS ${vtkSVIO_HEADERS}
    SOURCES ${vtkSVIO_SOURCES}
)
