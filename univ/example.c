#include "./univ.h"


int main(int argc, char **argv)
{

    // DEBUG ?
    SRE_DEBUGGING = 1;
    // DEBUG ?



    if (SRE_ring1_Init_Engine(24, 2, 800, 600) < 0)
    {
        SRE_Log("Error while initialising engine\n", NULL);
        return -1;
    }

    // SRE_ring0_3D_ExportDefaultTexturedCube();

    // Initialize camera and projection context
    SRE_ring1_Init_Drawing(45.0f, 0.1f, 100.0f);


    /* 3D cube with brick wall texture */
    
    SRE_ring1_Create_Full_Drawable("./WADs/complete_models/3D_cube", "./WADs/complete_models/3D_cube", "./WADs/textures/wall.jpg");




    // MAIN LOOP

    // bind the VAO
    glBindVertexArray(SRE_Main_Stack->drawable_list[0]->_VAO[SRE_Main_Stack->drawable_list[0]->_SELECTED_BUFFER]);
    // bind the Shader Program
    glUseProgram(SRE_Main_Stack->drawable_list[0]->_ShaderProgram[SRE_Main_Stack->drawable_list[0]->_SELECTED_SHADER]);
    // bind GL_TEXTURE0 to our brick wall texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SRE_Main_Stack->drawable_list[0]->_Texture[SRE_Main_Stack->drawable_list[0]->_SELECTED_TEXTURE]);


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
        SDL_GetWindowSize(SRE_Main_Stack->mainWindow, &SRE_Main_Stack->w, &SRE_Main_Stack->h);
        glViewport(0, 0, SRE_Main_Stack->w, SRE_Main_Stack->h);
        SRE_Main_Stack->projection_context->widthScreen = (float)SRE_Main_Stack->w;
        SRE_Main_Stack->projection_context->hightScreen = (float)SRE_Main_Stack->h;
        SRE_Main_Stack->projection_context->update(SRE_Main_Stack->projection_context);


        // check camera movements
        if (keys[SDL_SCANCODE_W])
        {
            // cam forward (zoom in)
            SRE_Main_Stack->camera->zPos -= 0.05f;
            SRE_Main_Stack->camera->zLook -= 0.05f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_S])
        {
            // cam backward (zoom out)
            SRE_Main_Stack->camera->zPos += 0.05f;
            SRE_Main_Stack->camera->zLook += 0.05f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // check model movements
        if (keys[SDL_SCANCODE_LEFT])
        {
            SRE_Main_Stack->drawable_list[0]->yRotAngle += 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            SRE_Main_Stack->drawable_list[0]->yRotAngle -= 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            SRE_Main_Stack->drawable_list[0]->xRotAngle += 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            SRE_Main_Stack->drawable_list[0]->xRotAngle -= 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }

        // update the whole 3D matrix
        SRE_ring1_Update_Transformation_Matrix(SRE_Main_Stack->drawable_list[0]->mvpLoc, *SRE_Main_Stack->drawable_list[0], *SRE_Main_Stack->camera, *SRE_Main_Stack->projection_context);


        // OPENGL: set a grey background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // DRAW IT
        // OPENGL: draw a shape
        glDrawElements(GL_TRIANGLES, SRE_Main_Stack->drawable_list[0]->_INDICES_BUFFLEN, GL_UNSIGNED_INT, 0);

        // SDL: render it.
        SDL_GL_SwapWindow(SRE_Main_Stack->mainWindow);


        // SDL: wait
        elapsed = SDL_GetTicks() - frameStart;
        if (elapsed < targetFrameTime)
        {
            SDL_Delay(targetFrameTime - elapsed);
        }
    }
    // MAIN LOOP





    // Proper exit...
    SRE_ring1_Exit_Engine();
    return 0;
}