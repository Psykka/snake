project('sdldemo', 'cpp',
    default_options: [
        'default_library=static',
        'warning_level=2',
        'cpp_std=c++17'
    ])

cc = meson.get_compiler('cpp')

if cc.get_id() == 'msvc'
    # add_project_arguments(['/MP', '/MD', '/std:c++17'], language: 'cpp')
endif


sdl2_dep = dependency('sdl2')

sourceFiles = []

subdir('src')

executable('snake', sourceFiles,
    dependencies: sdl2_dep,
    win_subsystem: 'windows')