/*
    How does this engine works ?
    It is designed to be modular:
        -ring 0: OpenGL stuff (low level GPU)
        -ring 1: 3D Logic and OOP Objects (low level 3D, designed to link your game and 3D operations easily, maybe GUI soon ?)
        -ring 2: Animations and game composer
        -ring 3: Your game
*/

#ifndef UNIV_H
#define UNIV_H


/* plateform independent includes */
#include <SDL3/SDL.h>
#include "./glad.h"
#include <cglm/cglm.h>
#include <stdio.h>


// PROGRAMMING, REMOVED WHEN PUSHING
#define PLATEFORM_LINUX 1
//#define PLATEFORM_WINDOWS 1
#define LVL2 1
// PROGRAMMING, REMOVED WHEN PUSHING


#ifdef PLATEFORM_LINUX
    #undef PLATEFORM_WINDOWS
    #include "../platforms/Linux/linux.c"
#elif PLATEFORM_WINDOWS
    #undef PLATEFORM_LINUX
    #include "../platforms/Windows/windows.c"
#endif


#ifdef LVL0
    #undef LVL1
    #undef LVL2
    #include "./ring0.h"
#elif LVL1
    #undef LVL0
    #undef LVL2
    #include "./ring0.h"
    #include "./ring1.h"
#elif LVL2
    #undef LVL0
    #undef LVL1
    #include "./ring0.h"
    #include "./ring1.h"
    #include "./ring2.h"
#endif


#endif
