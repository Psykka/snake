# snake
Snake game

using SLD2 and C++

![](https://i.imgur.com/HY31Ji6.gif)

# Building

Requirements:
 - Python and pip for installing the building tools
 - Any C/C++ compiler

## Installing building tools

```
$ pip install meson ninja
```

## Building project

```
# create builddir for meson
$ meson builddir

# compile project
$ meson compile -C builddir
```
