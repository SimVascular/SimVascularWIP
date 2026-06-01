set(vtkSV4ROMSimulation_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/sv4guiModuleROMSimulationExports.h)
set(vtkSV4ROMSimulation_HEADERS
    sv4gui_ROMSimulationUtils.h
    sv4gui_MitkROMSimJobIO.h
    sv4gui_MitkROMSimulationObjectFactory.h
    sv4gui_MitkROMSimJob.h
    sv4gui_ROMSimJob.h
    ${vtkSV4ROMSimulation_EXPORT_HEADER}
)

set(vtkSV4ROMSimulation_SOURCES
    sv4gui_ROMSimulationUtils.cxx
    sv4gui_ROMSimJob.cxx
    sv4gui_MitkROMSimJobIO.cxx
    sv4gui_MitkROMSimJob.cxx
    sv4gui_MitkROMSimulationObjectFactory.cxx
)

vtk_module_add_module(VTK::SV4ROMSimulation
    HEADERS ${vtkSV4ROMSimulation_HEADERS}
    SOURCES ${vtkSV4ROMSimulation_SOURCES}
)
generate_export_header(VTK::SV4ROMSimulation
    BASE_NAME "SV4GUIMODULEROMSIMULATION"
    EXPORT_FILE_NAME ${vtkSV4ROMSimulation_EXPORT_HEADER}
)