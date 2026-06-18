set(vtkSV4Simulation_HEADERS
    sv4gui_MitkSimulationObjectFactory.h
    sv4gui_MitkSimJobIO.h
    sv4gui_MitkSimJob.h
    sv4gui_SimJob.h
    sv4gui_SimulationUtils.h
    sv4gui_SimXmlWriter.h
    ${vtkSV4Simulation_EXPORT_HEADER}
)

set(vtkSV4Simulation_SOURCES
    sv4gui_SimulationUtils.cxx
    sv4gui_MitkSimJob.cxx
    sv4gui_SimXmlWriter.cxx
    sv4gui_SimJob.cxx
    sv4gui_MitkSimJobIO.cxx
    sv4gui_MitkSimulationObjectFactory.cxx
)

vtk_module_add_module(VTK::SV4Simulation
    HEADERS ${vtkSV4Simulation_HEADERS}
    SOURCES ${vtkSV4Simulation_SOURCES}
)