import re
import sys
from pathlib import Path

root = Path('~/src/simvascular/simvascularwip/Source').expanduser()

name_to_path: dict[str, Path] = {}
dependencies: dict[str, list[str]] = {}  # key #includes<value>

extra_roots = [
    Path('~/src/simvascular/simvascularwip/cmake-build-relwithdebinfo/SuperBuild/VTK').expanduser(),
    Path('~/src/simvascular/simvascularwip/cmake-build-relwithdebinfo/SuperBuild/MITK').expanduser(),
]

extra_name_to_paths: dict[Path, dict[str, Path]] ={
    extra_root: {
        path.name: path.relative_to(extra_root)
        for path in [
            *extra_root.rglob('*.h'),
            *extra_root.rglob('*.hxx'),
            *extra_root.rglob('*.cxx'),
        ]
    }
    for extra_root in extra_roots
}

for path in [
    *root.rglob('*.h'),
    *root.rglob('*.hxx'),
    *root.rglob('*.cxx'),
]:
    assert path.name not in name_to_path, f'{path} is not unique'
    name_to_path[path.name] = path.relative_to(root)

for path in name_to_path.values():
    deps = dependencies[path.name] = []
    for line in root.joinpath(path).read_text().splitlines():
        if line.startswith('#include'):
            dep = re.match(r'#include *[<"](.*?)[>"]', line)[1]
            if dep not in dependencies:
                dependencies[dep] = []
            deps.append(dep)


def names_in_path(query):
    return sorted({name for name, path in name_to_path.items() if path.is_relative_to(query)})


def query_includes(query):
    query_names = names_in_path(query)
    return sorted({
        dep
        for name in query_names
        for dep in dependencies[name]
    })


def includes_query(query):
    query_names = names_in_path(query)
    return sorted({
        name
        for name, deps in dependencies.items()
        if any(dep in deps for dep in query_names)
    })


# mod = 'sv/Mesh/VMTKUtils'
_, mod = sys.argv

print(f'{mod} depends on these')
print()
print(*sorted([f'  "{name}"' for name in query_includes(mod) if name not in name_to_path and all(name not in extra_name_to_path for extra_name_to_path in extra_name_to_paths.values())]), sep='\n')
for extra_root, extra_name_to_path in extra_name_to_paths.items():
    print()
    print(extra_root)
    print(*sorted([f'  {extra_name_to_path[name]}' for name in query_includes(mod) if name not in name_to_path and name in extra_name_to_path]), sep='\n')
print()
print(root)
print(*sorted([f'  {name_to_path[name]}' for name in query_includes(mod) if name in name_to_path]), sep='\n')
print()

print(f'these depend on {mod}')
print()
print(*sorted([f'  {name_to_path[name]}' for name in includes_query(mod)]), sep='\n')
print()
