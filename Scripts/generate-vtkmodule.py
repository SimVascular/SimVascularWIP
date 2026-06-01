from pathlib import Path

root = Path('~/src/simvascular/simvascularwip/Source').expanduser()

name_paths: dict[str, Path] = {}

for mod_path in root.rglob('vtk.module'):
    parent = mod_path.parent

    group = mod_path.relative_to(root).parts[0].upper()

    name = str(mod_path.relative_to(root).parent).replace('/', '').replace('Modules', '')
    if name.startswith('vtk'):
        name = 'VTK::' + name.removeprefix('vtk')
    elif name.startswith('sv4gui'):
        name = 'VTK::SV4' + name.removeprefix('sv4gui')
    elif name.startswith('sv'):
        name = 'VTK::SV' + name.removeprefix('sv')
    else:
        name = 'VTK::SV' + name

    name_paths[name] = mod_path

    libname = 'vtk' + name.removeprefix('VTK::')

    headers = [*parent.rglob('*.h'), *parent.rglob('*.hxx')]
    sources = [*parent.rglob('*.cxx')]

    headers = [path.relative_to(parent) for path in headers]
    sources = [path.relative_to(parent) for path in sources]

    with mod_path.open('w') as f:
        f.write(f'NAME\n    {name}\nLIBRARY_NAME\n    {libname}\nGROUPS\n    SV\n    {group}\nDEPENDS\n')
        deps = [
            'VTK::CommonCore',
        ]
        if name != 'VTK::SVInclude':
            deps.insert(0, 'VTK::SVInclude')
        for dep in deps:
            f.write(f'    {dep}\n')

    with parent.joinpath('CMakeLists.txt').open('w') as f:
        if group != 'VTKSV':
            f.write(f'set({libname}_EXPORT_HEADER ${{CMAKE_CURRENT_BINARY_DIR}}/sv{parent.name}Exports.h)\n')
            headers.append(f"${{{libname}_EXPORT_HEADER}}")

        f.write(f'set({libname}_HEADERS\n    {"\n    ".join(str(x) for x in headers)}\n)\n\n')
        f.write(f'set({libname}_SOURCES\n    {"\n    ".join(str(x) for x in sources)}\n)\n\n')

        f.write(
            f'vtk_module_add_module({name}\n    HEADERS ${{{libname}_HEADERS}}\n    SOURCES ${{{libname}_SOURCES}}\n')
        if not sources:
            f.write("    HEADER_ONLY\n")
        f.write(')\n')

        if group != 'VTKSV':
            f.write(f'generate_export_header({name}\n'
                    f'    EXPORT_MACRO_NAME "SV_EXPORT_{parent.name.upper()}"\n'
                    f'    EXPORT_FILE_NAME ${{{libname}_EXPORT_HEADER}}\n'
                    f')')
