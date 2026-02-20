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


    /* RECTANGLE */

    // Initialize camera and projection context
    SRE_ring1_Init_Drawing(45.0f, 0.1f, 100.0f);
    
    // create a 3D Tetrahedron matrix object
    SRE_Main_Stack->model_list[0] = SRE_ring1_Create_Model_Object(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    // create the default shader program
    SRE_ring1_Append_Model_Shader(SRE_Main_Stack->model_list[0], "./WADs/complete_models/3D_cube");
    SRE_Main_Stack->model_list[0]->_SELECTED_SHADER = 0;

    // create the 3D cube's shape (vertices, indices, GLBuffers, etc...)
    SRE_ring1_Append_Model_VerticesAndIndices(SRE_Main_Stack->model_list[0], "./WADs/complete_models/3D_cube");

    // create the brick wall texture
    SRE_ring0_CreateTextureFromFile("./WADs/textures/wall.jpg", SRE_Main_Stack->model_list[0]->_Texture[SRE_Main_Stack->model_list[0]->_SELECTED_TEXTURE]);

    // get the uMVP uniform from our default OpenGL 3D Shader Program
    SRE_Main_Stack->model_list[0]->mvpLoc = SRE_ring0_Get_Uniform_TransformationMatrix_From_ShaderProgram(SRE_Main_Stack->model_list[0]->_ShaderProgram[SRE_Main_Stack->model_list[0]->_SELECTED_SHADER]);




    // MAIN LOOP
    int w, h;

    // bind the VAO
    glBindVertexArray(SRE_Main_Stack->model_list[0]->_VAO[SRE_Main_Stack->model_list[0]->_SELECTED_BUFFER]);
    // bind the Shader Program
    glUseProgram(SRE_Main_Stack->model_list[0]->_ShaderProgram[SRE_Main_Stack->model_list[0]->_SELECTED_SHADER]);
    // bind GL_TEXTURE0 to our brick wall texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SRE_Main_Stack->model_list[0]->_Texture[SRE_Main_Stack->model_list[0]->_SELECTED_TEXTURE]);


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
        SDL_GetWindowSize(SRE_Main_Stack->mainWindow, &w, &h);
        glViewport(0, 0, w, h);
        SRE_Main_Stack->projection_context->widthScreen = (float)w;
        SRE_Main_Stack->projection_context->hightScreen = (float)h;
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
            SRE_Main_Stack->model_list[0]->yRotAngle += 1.0f;
            SRE_Main_Stack->model_list[0]->update(SRE_Main_Stack->model_list[0]);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            SRE_Main_Stack->model_list[0]->yRotAngle -= 1.0f;
            SRE_Main_Stack->model_list[0]->update(SRE_Main_Stack->model_list[0]);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            SRE_Main_Stack->model_list[0]->xRotAngle += 1.0f;
            SRE_Main_Stack->model_list[0]->update(SRE_Main_Stack->model_list[0]);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            SRE_Main_Stack->model_list[0]->xRotAngle -= 1.0f;
            SRE_Main_Stack->model_list[0]->update(SRE_Main_Stack->model_list[0]);
        }

        // update the whole 3D matrix
        SRE_ring1_Update_Transformation_Matrix(SRE_Main_Stack->model_list[0]->mvpLoc, *SRE_Main_Stack->model_list[0], *SRE_Main_Stack->camera, *SRE_Main_Stack->projection_context);


        // OPENGL: set a grey background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // DRAW IT
        // OPENGL: draw a shape
        glDrawElements(GL_TRIANGLES, SRE_Main_Stack->model_list[0]->_INDICES_BUFFLEN, GL_UNSIGNED_INT, 0);

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
    SRE_ring1_Destroy_Model_Object(SRE_Main_Stack->model_list[0]);
    free(SRE_Main_Stack->camera);
    free(SRE_Main_Stack->projection_context);
    SRE_ring1_Exit_Engine();
    return 0;
}