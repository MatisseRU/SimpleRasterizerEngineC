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


    // Infos about the graphics card driver...
    printf("Your OpenGL version: %s\n", glGetString(GL_VERSION));

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    printf("Your graphics card can handle %d vertex attributes\n", nrAttributes);





    /* LET'S GO */

    glViewport(0, 0, 800, 600);

    
    // Create a simple OpenGL pipeline (program)
    unsigned int shaderProgram = SRE_3D_CreateDefaultCornerColoredShaderProgram();

    /* TRIANGLE */

    // 1 vertex mem size   *   1 triangle pack of mem size   *   how many triangles do we want to store
    //        6            *                 3               *                       20 (or more)
    unsigned int nbr_of_vertices = 6*4;
    float vertices[6*4] = {
     0.0f,  0.8165f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.2887f, 0.5f,   0.0f, 1.0f, 0.0f,
     0.5f, -0.2887f, 0.5f,   0.0f, 0.0f, 1.0f,
     0.0f, -0.2887f, -0.5f,  1.0f, 1.0f, 0.0f
    };

    unsigned int nbr_of_indices = 12;
    unsigned int indices[3*4] = {  // note that we start from 0!
    0, 1, 2,
    0, 2, 3,
    0, 3, 1,
    1, 3, 2
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


    // CGLM: 3D !!
    mat4 model, view, projection, mvp;

    // our translation / rotation matrix
    glm_mat4_identity(model);

    // the camera's movements matrix
    glm_lookat((vec3){0.0f, 0.0f, 3.0f}, // camera position
           (vec3){0.0f, 0.0f, 0.0f}, // where it's looking at
           (vec3){0.0f, 1.0f, 0.0f}, // in which direction is the top of the camera
           view);

    // sets up FOV and how we should get perspective effects
    glm_perspective(glm_rad(45.0f), 800.0f/600.0f, 0.1f, 100.0f, projection);

    // get the uniform in our shader
    int mvpLoc = glGetUniformLocation(shaderProgram, "uMVP");






    // MAIN LOOP
    float cameraZ = 3.0f; // used to move the camera forward and backward
    float time = SDL_GetTicks() / 1000.0f; // used to define the triangle's rotations
    int w, h;

    glBindVertexArray(VAO);

    SDL_Event ev;
    const uint8_t *keys = SDL_GetKeyboardState(NULL);

    uint8_t run = 1;    
    while (run)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_EVENT_QUIT)
            {
                run = 0;
            }
        }

        // Select our OpenGL Shader Program
        glUseProgram(shaderProgram);




        /* Update Viewport */
        
        SDL_GetWindowSize(mainWindow, &w, &h);
        glViewport(0, 0, w, h);
        glm_perspective(glm_rad(45.0f), (float)w / (float)h, 0.1f, 100.0f, projection);


        // check camera movements
        if (keys[SDL_SCANCODE_W]) cameraZ -= 0.05f; // cam forward (zoom in)
        if (keys[SDL_SCANCODE_S]) cameraZ += 0.05f; // cam backward (zoom out)
        
        glm_lookat((vec3){0.0f, 0.0f, cameraZ},
           (vec3){0.0f, 0.0f, 0.0f},
           (vec3){0.0f, 1.0f, 0.0f},
           view);


        // Rotating triangle
        time = SDL_GetTicks() / 1000.0f;

        glm_mat4_identity(model); // reset the model matrix
        glm_rotate(model, time, (vec3){0.0f, 1.0f, 0.0f}); // apply rotation

        // update the whole 3D matrix
        glm_mat4_mulN((mat4 *[]){&projection, &view, &model}, 3, mvp);
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (float *)mvp);



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