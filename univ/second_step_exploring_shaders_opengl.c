// PROGRAMMING, REMOVED WHEN PUSHING
#define PLATEFORM_LINUX 1
// PROGRAMMING, REMOVED WHEN PUSHING


#ifdef PLATEFORM_LINUX
    #undef PLATEFORM_WINDOWS
    #include "../platforms/Linux/linux.c"
#elif PLATEFORM_WINDOWS
    #undef PLATEFORM_LINUX
    #include "../plateforms/windows/windows.c"
#endif


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



    // SDL
    
    SDL_Window *mainWindow = SDL_CreateWindow("Main Test", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (mainWindow == NULL)
    {
        fprintf(stderr, "Failed at SDL_CreateWindow: \n%s\n", SDL_GetError());
        SDL_DestroyWindow(mainWindow);
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


    // Infos about the graphics card driver...
    printf("Your OpenGL version: %s\n", glGetString(GL_VERSION));

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    printf("Your graphics card can handle %d vertex attributes\n", nrAttributes);





    /* LET'S GO */

    
    // Create a simple OpenGL pipeline (program)
    unsigned int shaderProgram = SRE_CreateDefaultCornerColoredShaderProgram();

    /* RECTANGLE */

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };


    // Create VAO and VBO and EBO
    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);


    // Bind VAO and VBO and EBO
    // VAO
    glBindVertexArray(VAO);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    // Store vertices postitions and indices, also specify the size of the vector and the starting pointer to the position data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // valable for VAO VBO
    glEnableVertexAttribArray(0);
    // Store the vertices color, also specify the size of the vector and the starting pointer to the color data.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // valable for VAO VBO
    glEnableVertexAttribArray(1);



    // Clean up: unbind VAO and VBO
    // VAO
    glBindVertexArray(0);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);






    // MAIN LOOP

    uint8_t run = 1;
    SDL_Event ev;
    while (run)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_EVENT_QUIT)
            {
                run = 0;
            }
        }

        /* Update Viewport */

        int w, h;
        SDL_GetWindowSize(mainWindow, &w, &h);
        glViewport(0, 0, w, h);


        /* Back Ground */

        // OPENGL: set a grey background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        /* Our Shapes */

        // graphics pipeline (shader program)
        // OPENGL: use our graphics pipeline and shaders
        glUseProgram(shaderProgram);

        // DRAW IT
        // OPENGL: draw a shape
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // SDL: render it.
        SDL_GL_SwapWindow(mainWindow);
        // SDL: wait
        SDL_Delay(8);

    }

    // MAIN LOOP





    // Proper exit...
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}