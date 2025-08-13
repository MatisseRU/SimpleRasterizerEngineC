#define STB_IMAGE_IMPLEMENTATION
#include "../univ/stb_image.h"
#include "../univ/univ.h"


int main(int argc, char **argv)
{
    // SDL

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Failed at SDL_Init: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }else
    {
        printf("Initialised SDL, version: %d\n", SDL_GetVersion());
    }


    // OPENGL


    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute major version setting: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute minor version setting: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute profile mask core: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute double buffering: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute depth size: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute multisamplebuffers: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2))
    {
        fprintf(stderr, "Failed at SDL_GL_SetAttribute multisamples: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }



    // SDL
    
    SDL_Window *mainWindow = SDL_CreateWindow("Main Test", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (mainWindow == NULL)
    {
        fprintf(stderr, "Failed at SDL_CreateWindow: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }


    
    // OPENGL

    SDL_GLContext mainWindowGL_ctx = SDL_GL_CreateContext(mainWindow);
    if (mainWindowGL_ctx == NULL)
    {
        fprintf(stderr, "Failed at SDL_GL_CreateContext: \n%s\n", SDL_GetError());
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);


    // Infos about the graphics card driver...
    printf("Your OpenGL version: %s\n", glGetString(GL_VERSION));

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    printf("Your graphics card can handle %d vertex attributes\n", nrAttributes);

    int maxSamples;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    printf("Max MSAA samples: %d\n", maxSamples);





    /* LET'S GO */

    glViewport(0, 0, 800, 600);

    
    // Create a simple OpenGL pipeline (program)
    unsigned int shaderProgram = SRE_3D_CreateDefaultTexturedShaderProgram();

    /* TRIANGLE */

    // 1 vertex mem size   *   1 triangle pack of mem size   *   how many triangles do we want to store
    //        6            *                 3               *                       20 (or more)
    unsigned int nbr_of_vertices = 24;
    float vertices[24*5] = {
        // behind (-Z)
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,

        // forward (+Z)
        -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,

        // left (-X)
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,   1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,

        // right (+X)
        1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
        1.0f,  1.0f, -1.0f,   1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        1.0f, -1.0f,  1.0f,   0.0f, 1.0f,

        // up (+Y)
        -1.0f,  1.0f, -1.0f,   0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,

        // bottom (-Y)
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,   0.0f, 1.0f
    };

    unsigned int nbr_of_indices = 36;
    unsigned int indices[36] =
    {
        0, 1, 2, 2, 3, 0,       // behind
        4, 5, 6, 6, 7, 4,       // forward
        8, 9,10,10,11, 8,       // left
        12,13,14,14,15,12,       // right
        16,17,18,18,19,16,       // up
        20,21,22,22,23,20        // bottom
    };



    /* OpenGL Textures */

    // Load texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *textureLoaded = stbi_load("/home/lenovo/Documents/Info/GameEngine/SimpleRasterizerEngineC/examples-univ/WADs/textures/wall.jpg", &width, &height, &nrChannels, 0);

    if (textureLoaded == NULL)
    {
        fprintf(stderr, "\nFailed to load texture : \n%s\n\n", stbi_failure_reason());
    }else
    {
        printf("Image texture loaded:\nwidth: %d\nheight :%d\nchannels: %d\n", width, height, nrChannels);
    }


    // Create an OpenGL texture
    unsigned int textureCreated;
    glGenTextures(1, &textureCreated);
    glBindTexture(GL_TEXTURE_2D, textureCreated);

    // Wrapping settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Format RGB
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureLoaded);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureLoaded);



    // Create VAO and VBO and EBO
    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);


    // Bind VAO and VBO and EBO
    // VAO
    glBindVertexArray(VAO);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    // Store vertices postitions and indices, also specify the size of the vector and the starting pointer to the position data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // valable for VAO VBO and EBO
    glEnableVertexAttribArray(0);
    // Store the vertices color, also specify the size of the vector and the starting pointer to the texture coords.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // valable for VAO VBO and EBO
    glEnableVertexAttribArray(1);


    // CGLM: 3D !!

    // create a 3D Projection matrix object
    SRE_Projection *projection_context = SRE_Create_Projection_Object(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    // create a 3D Camera matrix object
    SRE_View *camera = SRE_Create_View_Object(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // create a 3D Tetrahedron matrix object
    SRE_Model *cube_model = SRE_Create_Model_Object(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


    // Get the uMVP uniform from our default OpenGL 3D Shader Program
    int mvpLoc = SRE_Get_Uniform_TransformationMatrix_From_ShaderProgram(shaderProgram);




    // MAIN LOOP
    int w, h;

    glBindVertexArray(VAO);
    glUseProgram(shaderProgram);

    // bind GL_TEXTURE0 to our own texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureCreated);
    // get the uniform
    int uniLoc = glGetUniformLocation(shaderProgram, "ourTexture");
    glUniform1i(uniLoc, 0);

    SDL_Event ev;
    const uint8_t *keys = SDL_GetKeyboardState(NULL);

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




        /* Update Viewport */
        
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
        SRE_Update_Transformation_Matrix(mvpLoc, *cube_model, *camera, *projection_context);



        /* Back Ground */

        // OPENGL: set a grey background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        /* Our Shapes */

        // DRAW IT
        // OPENGL: draw a shape
        glDrawElements(GL_TRIANGLES, nbr_of_indices, GL_UNSIGNED_INT, 0);

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
    free(cube_model);
    free(camera);
    free(projection_context);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}