set(vtkSV4MultiPhysics_EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/svMultiPhysicsExports.h)
set(vtkSV4MultiPhysics_HEADERS
    sv4gui_MultiPhysicsJob.h
    sv4gui_MitkMultiPhysicsJob.h
    sv4gui_MitkMultiPhysicsJobIO.h
    sv4gui_MitkMultiPhysicsObjectFactory.h
    sv4gui_MultiPhysicsbcClass.h
    sv4gui_MultiPhysicsViscosity.h
    sv4gui_XmlWriter.h
    sv4gui_MultiPhysicseqClass.h
    ${vtkSV4MultiPhysics_EXPORT_HEADER}
)

set(vtkSV4MultiPhysics_SOURCES
    sv4gui_MitkMultiPhysicsJobIO.cxx
    sv4gui_MultiPhysicsViscosity.cxx
    sv4gui_MitkMultiPhysicsObjectFactory.cxx
    sv4gui_MitkMultiPhysicsJob.cxx
    sv4gui_MultiPhysicsbcClass.cxx
    sv4gui_MultiPhysicsJob.cxx
    sv4gui_MultiPhysicseqClass.cxx
    sv4gui_XmlWriter.cxx
)

vtk_module_add_module(VTK::SV4MultiPhysics
    HEADERS ${vtkSV4MultiPhysics_HEADERS}
    SOURCES ${vtkSV4MultiPhysics_SOURCES}
)
generate_export_header(VTK::SV4MultiPhysics
    EXPORT_MACRO_NAME "SV_EXPORT_MULTIPHYSICS"
    EXPORT_FILE_NAME ${vtkSV4MultiPhysics_EXPORT_HEADER}
)