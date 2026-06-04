set(VTK_GROUP_ENABLE_SV "YES")

vtk_module_find_modules(module_files "${CMAKE_CURRENT_SOURCE_DIR}")
vtk_module_scan(
        MODULE_FILES ${module_files}
        PROVIDES_MODULES modules
)
vtk_module_build(
        MODULES ${modules}
        INSTALL_EXPORT VTKSV
)


if (${SV_WRAP_PYTHON})
    vtk_module_python_default_destination(python_destination)
    vtk_module_wrap_python(
            MODULES ${modules}
            BUILD_PYI_FILES ON
            INSTALL_HEADERS OFF
            MODULE_DESTINATION ${python_destination}
            PYTHON_PACKAGE "sv"
    )
endif ()