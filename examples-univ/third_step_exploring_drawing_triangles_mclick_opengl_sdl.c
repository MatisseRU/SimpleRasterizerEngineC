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

    glViewport(0, 0, 800, 600);

    
    // Create a simple OpenGL pipeline (program)
    unsigned int shaderProgram = SRE_CreateDefaultCornerColoredShaderProgram();

    /* TRIANGLE */

    // 1 vertex mem size   *   1 triangle pack of mem size   *   how many triangles do we want to store
    //        6            *                 3               *                       20 (or more)
    // Total program memory consumption ~1.64 Kb.
    unsigned int nbr_of_vertices = 6*3;
    float vertices[6*3*20] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    // 
    unsigned int nbr_of_indices = 3;
    unsigned int indices[3*20] = {  // note that we start from 0!
    0, 1, 2
    };



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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // valable for VAO VBO and EBO
    glEnableVertexAttribArray(0);
    // Store the vertices color, also specify the size of the vector and the starting pointer to the color data.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // valable for VAO VBO and EBO
    glEnableVertexAttribArray(1);



    // MAIN LOOP
    int w, h;
    float mouseX, mouseY;

    float normX = 0.0f;
    float normY = 0.0f;

    int nbr_of_new_vertices = 0;
    uint8_t nbr_of_new_indices = 0;
    float new_vertices[6*3];
    float new_indices[3];

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

            // Test if we already have 3 new vertices
            if (nbr_of_new_indices == 3)
            {
                // add the new vertices to the vertex buffer
                printf("New vertices:\n"); // DEBUG
                for (unsigned int i = 0; i != nbr_of_new_vertices; i += 6)
                {
                    // DEBUG
                    printf("Vertex n°%u: %f, %f, %f of color red: %f, %f, %f\n", (i+1), new_vertices[i], new_vertices[i+1], new_vertices[i+2], new_vertices[i+3], new_vertices[i+4], new_vertices[i+5]);
                    // DEBUG

                    vertices[nbr_of_vertices + i + 0] = new_vertices[i + 0];
                    vertices[nbr_of_vertices + i + 1] = new_vertices[i + 1];
                    vertices[nbr_of_vertices + i + 2] = new_vertices[i + 2];

                    vertices[nbr_of_vertices + i + 3] = new_vertices[i + 3];
                    vertices[nbr_of_vertices + i + 4] = new_vertices[i + 4];
                    vertices[nbr_of_vertices + i + 5] = new_vertices[i + 5];
                }
                nbr_of_vertices += 6*3;


                // add the new indices to the indice buffer
                indices[nbr_of_indices + 0] = new_indices[0];
                indices[nbr_of_indices + 1] = new_indices[1];
                indices[nbr_of_indices + 2] = new_indices[2];
                nbr_of_indices += 3;


                // Update OpenGL
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                
                // DEBUG

                printf("\n\nAll of the vertices:\n");
                for (unsigned int i = 0; i != nbr_of_vertices; i += 6)
                {
                    printf("Vertex n°%u: %f, %f, %f of color red: %f, %f, %f\n", (i+1), vertices[i], vertices[i+1], vertices[i+2], vertices[i+3], vertices[i+4], vertices[i+5]);
                }

                printf("\n\nAll of the indices:\n");
                for (unsigned int i = 0; i != nbr_of_indices; i++)
                {
                    printf("Indice n°%u: %d\n", i, indices[i]);
                }
                
                // DEBUG


                // reset the check
                nbr_of_new_vertices = 0;
                nbr_of_new_indices = 0;
            }

            if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    // Get the current position of the mouse
                    SDL_GetMouseState(&mouseX, &mouseY);

                    normX = (mouseX / w) * 2.0f - 1.0f;
                    normY = 1.0f - (mouseY / h) * 2.0f;

                    // Append the new vertex to a temp buffer

                    // New vertex
                    // x   y   z      r   g   b
                    new_vertices[nbr_of_new_vertices + 0] = normX;
                    new_vertices[nbr_of_new_vertices + 1] = normY;
                    new_vertices[nbr_of_new_vertices + 2] = 0.0f;

                    new_vertices[nbr_of_new_vertices + 3] = 1.0f;
                    new_vertices[nbr_of_new_vertices + 4] = 0.0f;
                    new_vertices[nbr_of_new_vertices + 5] = 0.0f;

                    nbr_of_new_vertices += 6;

                    // New indice for that vertex
                    new_indices[nbr_of_new_indices] = nbr_of_indices + nbr_of_new_indices;
                    nbr_of_new_indices++;
                }
            }
        }

        /* Update Viewport */

        
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
        glDrawElements(GL_TRIANGLES, nbr_of_indices, GL_UNSIGNED_INT, 0);

        // SDL: render it.
        SDL_GL_SwapWindow(mainWindow);


        // SDL: wait
        SDL_Delay(32);

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