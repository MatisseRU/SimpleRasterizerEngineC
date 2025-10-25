#include "./univ.h"


int main(int argc, char **argv)
{

    // DEBUG ?
    SRE_DEBUGGING = 1;
    // DEBUG ?



    if (SRE_Init_Engine(24, 2, 800, 600) < 0)
    {
        SRE_Log("Error while initialising engine\n", NULL);
        return -1;
    }

    SRE_3D_ExportDefaultTexturedCube();


    /* RECTANGLE */

    // create a 3D Projection matrix object
    SRE_Projection *projection_context = SRE_Create_Projection_Object(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    // create a 3D Camera matrix object
    SRE_View *camera = SRE_Create_View_Object(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // create a 3D Tetrahedron matrix object
    SRE_Model *cube_model = SRE_Create_Model_Object(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    // create the default shader program
    cube_model->_SELECTED_SHADER = 0;
    cube_model->_ShaderProgram[cube_model->_SELECTED_SHADER] = SRE_3D_CreateDefaultTexturedShaderProgram();
    cube_model->_SHADER_PROGRAM_BUFFLEN = 1;

    // load vertices to the model
    cube_model->_VERTICES = read_floats_from_file("3D_cube.vert", (size_t *)&cube_model->_VERTICES_BUFFLEN);
    if (cube_model->_VERTICES == NULL)
    {
        SRE_Log("Failed to load vertices to cube model\n", NULL);
        return -1;
    }

    // load indices to the model
    cube_model->_INDICES = read_uints_from_file("3D_cube.indi", (size_t *)&cube_model->_INDICES_BUFFLEN);
    if (cube_model->_INDICES == NULL)
    {
        SRE_Log("Failed to load indices to cube model\n", NULL);
        return -1;
    }


    // save vertices and indices to buffers
    SRE_SaveModel_TO_GLBuffers(cube_model->_VAO[cube_model->_SELECTED_BUFFER], cube_model->_VBO[cube_model->_SELECTED_BUFFER], cube_model->_EBO[cube_model->_SELECTED_BUFFER], cube_model->_VERTICES, cube_model->_INDICES, sizeof(float) * cube_model->_VERTICES_BUFFLEN, cube_model->_VERTICES_BUFFLEN, sizeof(float) * cube_model->_INDICES_BUFFLEN, cube_model->_INDICES_BUFFLEN, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // create the brick wall texture
    SRE_CreateTextureFromFile("/home/lenovo/Documents/Info/GameEngine/SimpleRasterizerEngineC/examples-univ/WADs/textures/wall.jpg", cube_model->_Texture[cube_model->_SELECTED_TEXTURE]);
    
    // get the uMVP uniform from our default OpenGL 3D Shader Program
    cube_model->mvpLoc = SRE_Get_Uniform_TransformationMatrix_From_ShaderProgram(cube_model->_ShaderProgram[cube_model->_SELECTED_SHADER]);




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





    // Proper exit...
    SRE_Destroy_Model_Object(cube_model);
    free(camera);
    free(projection_context);
    SRE_Exit_Engine();
    return 0;
}