# SimpleRaycaster
Trying to make an open-source modular 3D Rasterizer in C using SDL3, OpenGL and CGLM.

# Building
Since this is a young project, things are not clearly established...

## requirements:
- SDL3
- CGLM
- GLAD (which is already included)

## organisation of the project
The main.c will be the game editor and example.c is an example on which I'm currently working with.

## building commands
build using:  
`make example`

if you need to pass extra flags to the compiler (path to an include folder) build using:  
`make example EXTRA_CFLAGS="-I../OpenGL/cglm/include/"`

build'n run:  
`make example EXTRA_CFLAGS="-I../OpenGL/cglm/include/" && ./build/example.out`