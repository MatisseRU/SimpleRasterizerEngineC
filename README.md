# SimpleRasterizerEngine
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
`make example EXTRA_CFLAGS=<FLAGS YOU NEED TO PASS TO THE COMPILER>`

build'n run example:  
`make example EXTRA_CFLAGS="-I../OpenGL/cglm/include/" && ./build/example.out`


# Technical Informations
This engine, as mentioned above, uses OpenGL 3.0 + CGLM for 3D Graphics Rendering and SDL3 to handle the windows, inputs and events.

## Engineering
This engine is modular, which means that you can either use OpenGL and basic useful functions alone (ring 0), use structures to manipulate easily OpenGL buffers, textures, vertices/indices and shader programs (ring 1), or use physics implementations (ring 2).

Your own full scene (or game) 's code is a ring 3 layer program, which might use ring 0 + ring 1 + ring 2 in most of the cases.

Any ressources used, such as textures (.jpg, .bmp, .png, ...), vertices (.vert), indices (.indi), vertex shaders (.vshader), fragment shaders (fshader) are situated in the WADs folder.

Every global variable, excepted macros, such as the main window handle, OpenGL contexts, the list of drawn models, the camera, etc... are stored in a structure found at ring 1: "SRE_Globals* SRE_Main_Stack".