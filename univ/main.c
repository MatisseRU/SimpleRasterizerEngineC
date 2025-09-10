#include "./univ.h"

/*
    How does it work ?

    1.) Rings
    -> Ring 0: low-level OpenGL, open and read files
    -> Ring 1: OOP
    -> Ring 2: game/animator code (user stuff)

    2.) OOP
    -> Each elemnt drawn to the screen has its own instance of SRE_Object
    -> Functions and methods are used to manipulate the objects (set object's coordinates, translations, ...)
    -> A "protagonist" object must be created, it defines the played character's position in the world and prevents floating numbers to lose precision at high coordinates.
    -> The protagonist object has its own class.

    3.) Coordinate system
    A classical coordinate system would be very limited due to how floating point numbers are represented in memory,
    as the coordinates get bigger and bigger, we lose more and more precision, going from around 7 digits down to 2 or 3 digits at high coords.
    A simple way to fix that is to tell CGLM and OpenGL that the center of the world is wherever our main caracter and camera are.
    This way, we keep objects rendered closely with excellent visuals, no scattering, no "shaking" vertices, etc...

    -> A int64 (x/y/z)protagonist_offset is used to keep track of the actual (approximative) coordinates of our character in the world.
    -> A float (x/y/z)protagonist_local_coords is used for matrix calculations in CGLM, those numbers will be very close to 0, thus keeping excellent precision as far as float types are involved.
    -> The global coordinates for the protagonist are calculated this way:
        (int64)global_coords = (int64)protagonist_offset  +  (float)protagonist_local_coords
    -->> This way, we can work without experiencing precision loss due to floating point numbers (we keep around 7 digits of precision).

    4.) What the engine is capable of
    -> Rendering objects with different models (multiple VAOs)
    -> Rendering objects with different textures (multiple texture slots)
    -> Rendering objects with different shaders (multiple shader programs)
    -> Rendering objects in 3D
    -> Rendering objects in motion (placing them on the 3D coords, moving them around...)
    -> (late) Rendering objects with graph / tree animation processing (child/parent object relations)
    -> (late) Rendering cinematics
    -> (late) AI
*/






int main(int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Failed at SDL_Init: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }else
    {
        printf("Initialised SDL, version: %d\n", SDL_GetVersion());
    }







    SDL_Quit();
    return 0;
}