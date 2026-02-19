#include "./univ.h"

/*
    How does it work ?

    1.) Rings
    -> Ring 0: low-level OpenGL, open and read files
    -> Ring 1: OOP
    -> Ring 2: game/animator code (user stuff)
    -> main.c: game editor (object editor, scene editor, game editor, animation editor, etc...)

    2.) OOP
    -> Each element drawn to the screen has its own instance of SRE_Object
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
        (int64)global_coords = (int64)protagonist_offset  +  (float rounded and converted to int64)protagonist_local_coords
    -> The local coordinates become:
        (float)protagonist_local_coords = (float)..._local_coords - (float)..._local_coords(INT PART)
    -->> This way, we can work without experiencing precision loss due to floating point numbers (we keep around 7 digits of precision).

    4.) What the engine is capable of
    -> Rendering objects with different models (multiple VAOs)
    -> Rendering objects with different textures (multiple texture slots)
    -> Rendering objects with different shaders (multiple shader programs)
    -> Rendering objects in 3D
    -> Rendering objects in motion (placing them on the 3D coords, moving them around...)
    -> (late) Rendering objects with graph animation processing (child/parent object relations linked together in pivot)
    -> (late) Rendering cinematics
    -> (late) AI
*/






int main(int argc, char **argv)
{

    // DEBUG ?
    if (argc > 1)
    {
        if (!strcmp(argv[1], "--debug"))
        {
            SRE_DEBUGGING = 1;
            printf("\nENABLED DEBUGGING\n");
        }
    }
    // DEBUG ?

    
    if (SRE_Init_Engine(24, 2, 800, 600) < 0)
    {
        SRE_Log("Error while initialising engine\n", NULL);
        return -1;
    }

    // create a 3D Projection matrix object
    SRE_Projection *projection_context = SRE_Create_Projection_Object(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    // create a 3D Camera matrix object
    SRE_View *camera = SRE_Create_View_Object(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    
















    /*
    // MAIN LOOP
    int w, h;

    // bind the VAO
    glBindVertexArray(cube_model->_VAO[cube_model->_SELECTED_BUFFER]);
    // bind the Shader Program
    glUseProgram(cube_model->_ShaderProgram[cube_model->_SELECTED_SHADER]);
    // bind GL_TEXTURE0 to our brick wall texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cube_model->_Texture[cube_model->_SELECTED_TEXTURE]);
    // get the 3D matrix uniform
    int uniLoc = glGetUniformLocation(cube_model->_ShaderProgram[cube_model->_SELECTED_SHADER], "ourTexture");
    glUniform1i(uniLoc, 0);


    SDL_Event ev;
    const bool *keys = SDL_GetKeyboardState(NULL);

    const int targetFrameTime = 1000 / 30; // 16 ms
    uint64_t elapsed, frameStart;

    uint8_t run = 1;
    while (run)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_EVENT_QUIT)
            {
                run = 0;
            }
        }


        // Update Viewport
        SDL_GetWindowSize(mainWindow, &w, &h);
        glViewport(0, 0, w, h);
        projection_context->widthScreen = (float)w;
        projection_context->hightScreen = (float)h;
        projection_context->update(projection_context);


        // check camera movements
        if (keys[SDL_SCANCODE_W])
        {
            // cam forward (zoom in)
            camera->zPos -= 0.05f;
            camera->zLook -= 0.05f;
            camera->update(camera);
        }
        if (keys[SDL_SCANCODE_S])
        {
            // cam backward (zoom out)
            camera->zPos += 0.05f;
            camera->zLook += 0.05f;
            camera->update(camera);
        }

        // check model movements
        if (keys[SDL_SCANCODE_LEFT])
        {
            cube_model->yRotAngle += 1.0f;
            cube_model->update(cube_model);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            cube_model->yRotAngle -= 1.0f;
            cube_model->update(cube_model);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            cube_model->xRotAngle += 1.0f;
            cube_model->update(cube_model);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            cube_model->xRotAngle -= 1.0f;
            cube_model->update(cube_model);
        }

        // update the whole 3D matrix
        SRE_Update_Transformation_Matrix(cube_model->mvpLoc, *cube_model, *camera, *projection_context);


        // OPENGL: set a grey background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // DRAW IT
        // OPENGL: draw a shape
        glDrawElements(GL_TRIANGLES, cube_model->_INDICES_BUFFLEN, GL_UNSIGNED_INT, 0);

        // SDL: render it.
        SDL_GL_SwapWindow(mainWindow);


        // SDL: wait
        elapsed = SDL_GetTicks() - frameStart;
        if (elapsed < targetFrameTime)
        {
            SDL_Delay(targetFrameTime - elapsed);
        }
    }
    // MAIN LOOP
*/




    SRE_Exit_Engine();
    return 0;
}