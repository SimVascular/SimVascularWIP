set(vtkSV4MultiPhysics_HEADERS
    sv4gui_MultiPhysicsJob.h
    sv4gui_MitkMultiPhysicsJob.h
    sv4gui_MitkMultiPhysicsJobIO.h
    sv4gui_MitkMultiPhysicsObjectFactory.h
    sv4gui_MultiPhysicsbcClass.h
    sv4gui_MultiPhysicsViscosity.h
    sv4gui_XmlWriter.h
    sv4gui_MultiPhysicseqClass.h
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

vtk_module_link(VTK::SV4MultiPhysics PUBLIC MitkCore Qt6::Core)

# TODO this is a hack. I'm not sure how this is actually supposed to be initialized.
vtk_module_definitions(VTK::SV4MultiPhysics PUBLIC US_MODULE_NAME='SV4MultiPhysics')
