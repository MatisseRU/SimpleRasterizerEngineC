# How does the engine SHOULD be designed:
## Modularity
- Ring 0: bare OpenGL, used to manipulate OpenGL's basic functionalities quickly and manage Object Oriented stuff manually (Vertices, models, camera, etc..)
- Ring 1: Object Oriented code, the core of the engine ; used to manipulate pre-defined "classes" of objects (structures) to "hide" all of the low-level operations in order to create a complete game without bothering with Graphics (OpenGL) and Coordination (Vertices, Shaders, etc...)
- Ring 2: Game Logic stuff: gravity, collisions, characters and interactions.
- Ring 3: Your Game !

## Conventions
### Function naming:
Every functions must be named respecting this convention:  
SRE_ringX_WhatItDoes(type parameter, type *parameter2, etc...)

The only exception to this rule is the SRE_Log() logger.

### Function usages:
- A function must stick to the very necessary and use the SRE_Log() function to log properly what's happenning (especially when errors occur).
- Do not confuse rings, if a ring 1 function needs a special OpenGL operation, please, write a new ring 0 function or modify the most appropriate one with the new feature as an option.

### File Extensions:
A model can be exported to different formats which are all necessary when rebuilding it in the engine:
- **.vert**: vertices' coordinates that define the model.
- **.indi**: indices, AKA, orders of the model's vertex in which it must be build.
- **.tex**: texture (any image used as a 2D texture)
- **.vshader**: vertex shader (OpenGL code) used for the model.
- **.fshader**: fragment shader (OpenGL code) used for the model.
- **.unils**: shaders' OpenGL uniform name list, used to properly load every uniform used to draw / calculate using Hardware Acceleration provided by OpenGL.



# Where do we go now ? (TODO):
## "Hard / abstract stuff", low-level programming and core engineering:
- Ring1-ify the creation AND manipulation of a model (vertices, indices, shader programs, shader uniforms, 3D matrix, positions, )
- Change "absolute positioning" to "global offset positioning" (since floats' precision shrink as the number gets bigger and bigger, the (0,0,0) will "move" with the controlled character, AKA the camera), the offset should be a int64 since coordinates might be huge at some point.
- Ring1-ify frame updating (drawing and shader program selection, FPS counter, etc...)

## "Affordable stuff", easy programming, affordable for junior-devs:
- Correct memory leaks !!!! (oups...), tips: `valgrind --leak-check=full --show-leak-kinds=all --verbose --log-file=valgrind_log.txt ./build/example.out` ; to sort logs: `grep -A 10 -B 2 "SRE_" valgrind_log.txt | grep -A 12 -B 2 "definitely lost\|indirectly lost\|possibly lost" > valgrind_log_sorted.txt`
- Add / reformat function descriptions using a standard C convention.
- Remove function descriptions from .c files since they are already specified in the right .h one.

## "Easy stuff", designing and testing:
- Test the available code (from example.c, see Build section in the README) with different textures, vertices and indices.
- Correct my poor English phrasing / orthograph... :'(  (I'm not focused on that)
