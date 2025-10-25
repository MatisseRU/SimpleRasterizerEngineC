#include "./ring1.h"

/* GLOBAL VARIABLES */

SDL_Window *mainWindow;
SDL_GLContext mainWindowGL_ctx;



/* Basic engine setup functions */

int SRE_Init_Engine(int depth_size, int multi_samples, int w_window, int h_window)
{
    // SDL

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SRE_Log("Failed at SDL_Init:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }else
    {
        char tempBuff[100];

        SRE_Log("Initialised SDL, version: ", NULL);
        sprintf(tempBuff, "%d", SDL_GetVersion());
        SRE_Log(tempBuff, NULL);
        SRE_Log("\n", NULL);
    }


    // OPENGL


    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3))
    {
        SRE_Log("Failed at SDL_GL_SetAttribute major version setting:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
    {
        SRE_Log("Failed at SDL_GL_SetAttribute minor version setting:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
    {
        SRE_Log("Failed at SDL_GL_SetAttribute profile mask core:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
    {
        SRE_Log("Failed at SDL_GL_SetAttribute double buffering:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }

    if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth_size))// default 24
    {
        SRE_Log("Failed at SDL_GL_SetAttribute depth size:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }

    if (multi_samples > 0)
    {
        if (!SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1))// default 1
        {
            SRE_Log("Failed at SDL_GL_SetAttribute multisamplebuffers:\n", NULL);
            SRE_Log(SDL_GetError(), NULL);
            SRE_Log("\n", NULL);
            SDL_Quit();
            return -1;
        }

        if (!SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multi_samples))// default 2
        {
            SRE_Log("Failed at SDL_GL_SetAttribute multisamples:\n", NULL);
            SRE_Log(SDL_GetError(), NULL);
            SRE_Log("\n", NULL);
            SDL_Quit();
            return -1;
        }
    }



    // SDL
    
    mainWindow = SDL_CreateWindow("Main Test", w_window, h_window, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);// default 800x600
    if (mainWindow == NULL)
    {
        SRE_Log("Failed at SDL_CreateWindow:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }


    
    // OPENGL

    mainWindowGL_ctx = SDL_GL_CreateContext(mainWindow);
    if (mainWindowGL_ctx == NULL)
    {
        SRE_Log("Failed at SDL_GL_CreateContext:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);


    // Infos about the graphics card driver...
    SRE_Log("Your OpenGL version:", NULL);
    SRE_Log((const char *)glGetString(GL_VERSION), NULL);
    SRE_Log("\n", NULL);

    int nrAttributes;
    char tempBuff[100];
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    sprintf(tempBuff, "%d", nrAttributes);
    SRE_Log("Your graphics card can handle ", NULL);
    SRE_Log(tempBuff, NULL);
    SRE_Log(" vertex attributes\n", NULL);

    int maxSamples;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    sprintf(tempBuff, "%d", maxSamples);
    SRE_Log("Max MSAA samples: ", NULL);
    SRE_Log(tempBuff, NULL);
    SRE_Log("\n", NULL);

    int maxTextureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    sprintf(tempBuff, "%d", maxTextureUnits);
    SRE_Log("Max texture slots (fragment shader): ", NULL);
    SRE_Log(tempBuff, NULL);
    SRE_Log("\n", NULL);

    int maxVertexTextureUnits;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureUnits);
    sprintf(tempBuff, "%d", maxVertexTextureUnits);
    SRE_Log("Max texture slots (vertex shader): ", NULL);
    SRE_Log(tempBuff, NULL);
    SRE_Log("\n", NULL);

    int maxCombinedTextureUnits;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureUnits);
    sprintf(tempBuff, "%d", maxCombinedTextureUnits);
    SRE_Log("Max combined texture slots (all shader stages): ", NULL);
    SRE_Log(tempBuff, NULL);
    SRE_Log("\n", NULL);

    glViewport(0, 0, 800, 600);

    return 0;
}
void SRE_Exit_Engine()
{
    // delete model objects

    // destroy the window
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return;
}


/* methods */

void SRE_Update_Transformation_Matrix(int mvpLoc, SRE_Model m, SRE_View v, SRE_Projection p)
{
    mat4 mvp;
    glm_mat4_mulN((mat4 *[]){&p.projection_matrix, &v.view_matrix, &m.model_matrix}, 3, mvp);
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (float *)mvp);
}
// update 3D context Projection matrix
void _SRE_Projection_do_Set_Settings(SRE_Projection *self)
{
    glm_perspective(self->fov, self->widthScreen / self->hightScreen, self->close, self->far, self->projection_matrix);
}
// place the camera by updating the View matrix
void _SRE_View_do_Place_At(SRE_View *self)
{
    glm_lookat((vec3){self->xPos, self->yPos, self->zPos},
               (vec3){self->xLook, self->yLook, self->zLook},
               (vec3){self->xTop, self->yTop, self->zTop},
               self->view_matrix);
}
// place the object model by updating the Model matrix
void _SRE_Model_do_Place_At(SRE_Model *self)
{
    glm_mat4_identity(self->model_matrix);
    glm_rotate(self->model_matrix, glm_rad(self->xRotAngle), (vec3){1, 0, 0});
    glm_rotate(self->model_matrix, glm_rad(self->yRotAngle), (vec3){0, 1, 0});
    glm_rotate(self->model_matrix, glm_rad(self->zRotAngle), (vec3){0, 0, 1});
    glm_translate(self->model_matrix, (vec3){self->xPos, self->yPos, self->zPos});
}



/* Constructors */

SRE_Projection *SRE_Create_Projection_Object(float fov_degrees, float width_screen, float hight_screen, float close_distance, float far_distance)
{
    SRE_Projection* projection = malloc(sizeof(SRE_Projection));
    if(projection == NULL)
    {
        SRE_Log("Failed to allocate memory for object\n", NULL);
        return NULL;
    }

    projection->update = _SRE_Projection_do_Set_Settings;

    projection->fov = glm_rad(fov_degrees);
    projection->widthScreen = width_screen;
    projection->hightScreen = hight_screen;
    projection->close = close_distance;
    projection->far = far_distance;
    projection->update(projection);

    return projection;
}
SRE_View *SRE_Create_View_Object(float x_pos, float y_pos, float z_pos, float x_look, float y_look, float z_look, float x_top, float y_top, float z_top)
{
    SRE_View* view = malloc(sizeof(SRE_View));
    if(view == NULL)
    {
        SRE_Log("Failed to allocate memory for object\n", NULL);
        return NULL;
    }

    view->update = _SRE_View_do_Place_At;

    view->xPos = x_pos;
    view->yPos = y_pos;
    view->zPos = z_pos;
    view->xLook = x_look;
    view->yLook = y_look;
    view->zLook = z_look;
    view->xTop = x_top;
    view->yTop = y_top;
    view->zTop = z_top;
    view->update(view);

    return view;
}
SRE_Model *SRE_Create_Model_Object(float x_pos, float y_pos, float z_pos, float x_rotation_angle_degrees, float y_rotation_angle_degrees, float z_rotation_angle_degrees, float x_scale, float y_scale, float z_scale)
{
    SRE_Model* model = malloc(sizeof(SRE_Model));
    if(model == NULL)
    {
        SRE_Log("Failed to allocate memory for object\n", NULL);
        return NULL;
    }

    model->update = _SRE_Model_do_Place_At;

    model->xPos = x_pos;
    model->yPos = y_pos;
    model->zPos = z_pos;
    model->xRotAngle = x_rotation_angle_degrees;
    model->yRotAngle = y_rotation_angle_degrees;
    model->zRotAngle = z_rotation_angle_degrees;
    model->xScale = x_scale;
    model->yScale = y_scale;
    model->zScale = z_scale;
    model->update(model);

    // VAO / VBO / EBO
    model->_BUFFER_BUFFLEN = 0;
    model->_SELECTED_BUFFER = 0;
    glGenVertexArrays(_SRE_MAX_GL_BUFFERS, model->_VAO);
    glGenBuffers(_SRE_MAX_GL_BUFFERS, model->_VBO);
    glGenBuffers(_SRE_MAX_GL_BUFFERS, model->_EBO);

    // Shaders
    model->_SHADER_PROGRAM_BUFFLEN = 0;
    model->_SELECTED_SHADER = 0;

    // Textures
    model->_TEXTURE_BUFFLEN = 0;
    model->_SELECTED_TEXTURE = 0;
    glGenTextures(_SRE_MAX_GL_TEXTURES, model->_Texture);

    return model;
}

void SRE_Destroy_Model_Object(SRE_Model *model)
{
    // delete VAO / VBO / EBO
    glDeleteVertexArrays(_SRE_MAX_GL_BUFFERS, model->_VAO);
    glDeleteBuffers(_SRE_MAX_GL_BUFFERS, model->_VBO);
    glDeleteBuffers(_SRE_MAX_GL_BUFFERS, model->_EBO);
    
    // delete Shader Programs
    for(uint32_t i = 0; i < model->_SHADER_PROGRAM_BUFFLEN; i++)
    {
        glDeleteProgram(model->_ShaderProgram[i]);
    }

    // delete Textures
    glDeleteTextures(_SRE_MAX_GL_TEXTURES, model->_Texture);

    // delete the vertices and indices buffer
    free(model->_VERTICES);
    free(model->_INDICES);

    // delete the model class.
    free(model);
}

