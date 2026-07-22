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

    # vtk_module_wrap_python() above only wraps VTK-style C++ classes; it
    # doesn't touch the plain CPython extension modules bundled in
    # VTK::SVPythonAPI (geometry, modeling, segmentation, meshing,
    # simulation, pathplanning, imaging, vmtk, mesh_utils), and it doesn't
    # generate a sv/__init__.py for the "sv" package it creates. Without an
    # __init__.py, "sv" only imports as an empty namespace package. Install
    # our own __init__.py, which loads those extension modules itself (see
    # Source/_PythonAPI/sv_package_init.py for why), so "import sv" works
    # and exposes sv.geometry/sv.modeling/etc. directly, in both the build
    # tree (for local testing) and a real install.
    set(sv_package_init_src "${CMAKE_CURRENT_SOURCE_DIR}/_PythonAPI/sv_package_init.py")
    set(sv_package_dir "${CMAKE_BINARY_DIR}/${python_destination}/sv")
    configure_file("${sv_package_init_src}" "${sv_package_dir}/__init__.py" COPYONLY)
    install(FILES "${sv_package_init_src}"
            DESTINATION "${python_destination}/sv"
            RENAME "__init__.py"
    )
endif ()