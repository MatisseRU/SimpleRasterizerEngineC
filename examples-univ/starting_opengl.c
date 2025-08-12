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

    printf("Your OpenGL version: %s\n", glGetString(GL_VERSION));


    
    // Create a simple OpenGL pipeline (program)
    unsigned int shaderProgram = SRE_CreateDefaultShaderProgram();


    /* Triangle */

    // vertices
    float vertices_triangle[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    // Create VAO and VBO
    // VAO
    unsigned int VAO_triangle;
    glGenVertexArrays(1, &VAO_triangle);
    // VBO
    unsigned int VBO_triangle;
    glGenBuffers(1, &VBO_triangle);


    // Bind VAO and VBO
    // VAO
    glBindVertexArray(VAO_triangle);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);


    // "Store" the vertices and specify its size and the starting pointer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Clean up: unbind VAO and VBO
    // VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // VBO
    glBindVertexArray(0);






    /* RECTANGLE */

    float vertices_rectangle[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int indices_rectangle[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };


    // Create VAO and VBO and EBO
    // VAO
    unsigned int VAO_rectangle;
    glGenVertexArrays(1, &VAO_rectangle);
    // VBO
    unsigned int VBO_rectangle;
    glGenBuffers(1, &VBO_rectangle);
    // EBO
    unsigned int EBO_rectangle;
    glGenBuffers(1, &EBO_rectangle);


    // Bind VAO and VBO and EBO
    // VAO
    glBindVertexArray(VAO_rectangle);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_rectangle);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_rectangle);


    // Store vertices and indices, also specify the size of the vertices and the starting pointer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rectangle), vertices_rectangle, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rectangle), indices_rectangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // valable for VAO VBO and EBO.
    glEnableVertexAttribArray(0);


    // Clean up: unbind VAO and VBO and EBO
    // VAO
    glBindVertexArray(0);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);






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

        /* Back Ground */

        // OPENGL: set a grey background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        /* Our Shapes */

        // graphics pipeline (shader program)
        // OPENGL: use our graphics pipeline and shaders
        glUseProgram(shaderProgram);


        // TRIANGLE
        // OPENGL: draw our triangle
        glBindVertexArray(VAO_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Use this function to work ONLY with VAOs and VBOs and so without EBOs.

        // SDL: render it.
        SDL_GL_SwapWindow(mainWindow);
        // SDL: wait 3 seconds
        SDL_Delay(3000);


        // RECTANGLE
        // OPENGL: draw a rectangle this time
        glBindVertexArray(VAO_rectangle);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Use this function to work with EBOs.

        // SDL: render it.
        SDL_GL_SwapWindow(mainWindow);
        // SDL: wait 3 seconds
        SDL_Delay(3000);

    }

    // MAIN LOOP





    // Proper exit...
    glDeleteVertexArrays(1, &VAO_triangle);
    glDeleteBuffers(1, &VBO_triangle);
    glDeleteVertexArrays(1, &VAO_rectangle);
    glDeleteBuffers(1, &VBO_rectangle);
    glDeleteBuffers(1, &EBO_rectangle);
    glDeleteProgram(shaderProgram);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}