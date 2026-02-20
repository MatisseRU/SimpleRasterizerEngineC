#include "./ring1.h"

/* GLOBAL VARIABLES */

SRE_Globals *SRE_Main_Stack;




/* Basic engine setup/exit functions */

int SRE_ring1_Init_Engine(int depth_size, int multi_samples, int w_window, int h_window)
{
    // Initialize the Main Stack of Engine
    SRE_Main_Stack = malloc(sizeof(SRE_Globals));
    if (SRE_Main_Stack == NULL)
    {
        SRE_Log("Failed to allocate memory for SRE_Main_Stack\n", NULL);
        return -1;
    }

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
    
    SRE_Main_Stack->mainWindow = SDL_CreateWindow("Main Test", w_window, h_window, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);// default 800x600
    if (SRE_Main_Stack->mainWindow == NULL)
    {
        SRE_Log("Failed at SDL_CreateWindow:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_Quit();
        return -1;
    }

    SRE_Main_Stack->w = w_window;
    SRE_Main_Stack->h = h_window;


    
    // OPENGL

    SRE_Main_Stack->mainWindowGL_ctx = SDL_GL_CreateContext(SRE_Main_Stack->mainWindow);
    if (SRE_Main_Stack->mainWindowGL_ctx == NULL)
    {
        SRE_Log("Failed at SDL_GL_CreateContext:\n", NULL);
        SRE_Log(SDL_GetError(), NULL);
        SRE_Log("\n", NULL);
        SDL_DestroyWindow(SRE_Main_Stack->mainWindow);
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
int SRE_ring1_Init_Drawing(float fov, float closest_distance, float farthest_distance)
{
    // create a 3D Projection matrix object
    SRE_Main_Stack->projection_context = SRE_ring1_Create_Projection_Object(fov, SRE_Main_Stack->w, SRE_Main_Stack->h, closest_distance, farthest_distance);
    SRE_Log("Successfully created the 3D projection context\n", NULL);

    // create a 3D Camera matrix object
    SRE_Main_Stack->camera = SRE_ring1_Create_View_Object(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    SRE_Log("Successfully created the camera\n", NULL);

    for (uint64_t i = 0; i < _SRE_MAX_OBJs_LIST; i++)
    {
        SRE_Main_Stack->drawable_list[i] = NULL;
    }

    SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN = 0;

    return 0;
}
void SRE_ring1_Exit_Engine()
{
    // delete model objects
    for (uint64_t i = 0; i < SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN; i++)
    {
        SRE_ring1_Destroy_Model_Object(SRE_Main_Stack->drawable_list[i]);
    }
    
    // delete camera
    free(SRE_Main_Stack->camera);
    // delete projection context
    free(SRE_Main_Stack->projection_context);

    // destroy the window
    SDL_DestroyWindow(SRE_Main_Stack->mainWindow);
    SDL_Quit();

    return;
}


/* methods */

void SRE_ring1_Update_Transformation_Matrix(int mvpLoc, SRE_ring1_Model m, SRE_ring1_View v, SRE_ring1_Projection p)
{
    mat4 mvp;
    glm_mat4_mulN((mat4 *[]){&p.projection_matrix, &v.view_matrix, &m.model_matrix}, 3, mvp);
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (float *)mvp);
}
// update 3D context Projection matrix
void _SRE_ring1_Projection_do_Set_Settings(SRE_ring1_Projection *self)
{
    glm_perspective(self->fov, self->widthScreen / self->hightScreen, self->close, self->far, self->projection_matrix);
}
// place the camera by updating the View matrix
void _SRE_ring1_View_do_Place_At(SRE_ring1_View *self)
{
    glm_lookat((vec3){self->xPos, self->yPos, self->zPos},
               (vec3){self->xLook, self->yLook, self->zLook},
               (vec3){self->xTop, self->yTop, self->zTop},
               self->view_matrix);
}
// place the object model by updating the Model matrix
void _SRE_ring1_Model_do_Place_At(SRE_ring1_Model *self)
{
    glm_mat4_identity(self->model_matrix);
    glm_rotate(self->model_matrix, glm_rad(self->xRotAngle), (vec3){1, 0, 0});
    glm_rotate(self->model_matrix, glm_rad(self->yRotAngle), (vec3){0, 1, 0});
    glm_rotate(self->model_matrix, glm_rad(self->zRotAngle), (vec3){0, 0, 1});
    glm_translate(self->model_matrix, (vec3){self->xPos, self->yPos, self->zPos});
}



/* Constructors */

SRE_ring1_Projection *SRE_ring1_Create_Projection_Object(float fov_degrees, float width_screen, float hight_screen, float close_distance, float far_distance)
{
    SRE_ring1_Projection* projection = malloc(sizeof(SRE_ring1_Projection));
    if(projection == NULL)
    {
        SRE_Log("Failed to allocate memory for object\n", NULL);
        return NULL;
    }

    projection->update = _SRE_ring1_Projection_do_Set_Settings;

    projection->fov = glm_rad(fov_degrees);
    projection->widthScreen = width_screen;
    projection->hightScreen = hight_screen;
    projection->close = close_distance;
    projection->far = far_distance;
    projection->update(projection);

    return projection;
}
SRE_ring1_View *SRE_ring1_Create_View_Object(float x_pos, float y_pos, float z_pos, float x_look, float y_look, float z_look, float x_top, float y_top, float z_top)
{
    SRE_ring1_View* view = malloc(sizeof(SRE_ring1_View));
    if(view == NULL)
    {
        SRE_Log("Failed to allocate memory for object\n", NULL);
        return NULL;
    }

    view->update = _SRE_ring1_View_do_Place_At;

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
SRE_ring1_Model *SRE_ring1_Create_Model_Object(float x_pos, float y_pos, float z_pos, float x_rotation_angle_degrees, float y_rotation_angle_degrees, float z_rotation_angle_degrees, float x_scale, float y_scale, float z_scale)
{
    SRE_ring1_Model* model = malloc(sizeof(SRE_ring1_Model));
    if(model == NULL)
    {
        SRE_Log("Failed to allocate memory for object\n", NULL);
        return NULL;
    }

    model->update = _SRE_ring1_Model_do_Place_At;

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

void SRE_ring1_Destroy_Model_Object(SRE_ring1_Model *model)
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

void SRE_ring1_Append_Model_Shader(SRE_ring1_Model *model, const char *shader_path)
{
    // default shaders
    if (strcmp(shader_path, "DefaultShaderProgram") == 0)
    {
        model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN] = SRE_ring0_CreateDefaultShaderProgram();
        model->_SHADER_PROGRAM_BUFFLEN += 1;
    }
    else if (strcmp(shader_path, "DefaultCornerColoredShaderProgram") == 0)
    {
        model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN] = SRE_ring0_CreateDefaultCornerColoredShaderProgram();
        model->_SHADER_PROGRAM_BUFFLEN += 1;
    }
    else if (strcmp(shader_path, "DefaultTexturedShaderProgram") == 0)
    {
        model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN] = SRE_ring0_CreateDefaultTexturedShaderProgram();
        model->_SHADER_PROGRAM_BUFFLEN += 1;
    }
    else if (strcmp(shader_path, "3D_DefaultCornerColoredShaderProgram") == 0)
    {
        model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN] = SRE_ring0_3D_CreateDefaultCornerColoredShaderProgram();
        model->_SHADER_PROGRAM_BUFFLEN += 1;
    }
    else if (strcmp(shader_path, "3D_DefaultTexturedShaderProgram") == 0)
    {
        model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN] = SRE_ring0_3D_CreateDefaultTexturedShaderProgram();
        model->_SHADER_PROGRAM_BUFFLEN += 1;
    }else
    {
        char vshader_path[8192];
        char fshader_path[8192];
        strncpy(vshader_path, shader_path, 8183);
        strncpy(fshader_path, shader_path, 8183);

        strcat(vshader_path, ".vshader");
        strcat(fshader_path, ".fshader");

        model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN] = SRE_ring0_3D_CreateShaderProgram_From_File(vshader_path, fshader_path);
        model->_SHADER_PROGRAM_BUFFLEN += 1;
    }

    if (model->_ShaderProgram[model->_SHADER_PROGRAM_BUFFLEN - 1] == 0)
    {
        model->_SHADER_PROGRAM_BUFFLEN--;

        char temp_buff[64];
        SRE_Log("Failed to create and append shader program n°", NULL);
        sprintf(temp_buff, "%u", model->_SHADER_PROGRAM_BUFFLEN);
        SRE_Log(temp_buff, NULL);
        SRE_Log(" to a model.\n", NULL);
    }
    else
    {
        char temp_buff[64];
        SRE_Log("Created and appended shader program n°", NULL);
        sprintf(temp_buff, "%u", model->_SHADER_PROGRAM_BUFFLEN - 1);
        SRE_Log(temp_buff, NULL);
        SRE_Log(" to a model.\n", NULL);
    }
}

void SRE_ring1_Append_Model_VerticesAndIndices(SRE_ring1_Model *model, const char *shape_path)
{

    char vert_path[8192];
    char indi_path[8192];

    strncpy(vert_path, shape_path, 8186);
    strncpy(indi_path, shape_path, 8186);
    strcat(vert_path, ".vert");
    strcat(indi_path, ".indi");

    // load vertices to the model
    model->_VERTICES = SRE_ring0_read_floats_from_file(vert_path, (size_t *)&model->_VERTICES_BUFFLEN);
    if (model->_VERTICES == NULL)
    {
        SRE_Log("Failed to load vertices to model\n", NULL);
    }

    // load indices to the model
    model->_INDICES = SRE_ring0_read_uints_from_file(indi_path, (size_t *)&model->_INDICES_BUFFLEN);
    if (model->_INDICES == NULL)
    {
        SRE_Log("Failed to load indices to model\n", NULL);
    }

    // save vertices and indices to buffers
    SRE_ring0_SaveModel_TO_GLBuffers(model->_VAO[model->_SELECTED_BUFFER], model->_VBO[model->_SELECTED_BUFFER], model->_EBO[model->_SELECTED_BUFFER], model->_VERTICES, model->_INDICES, sizeof(float) * model->_VERTICES_BUFFLEN, model->_VERTICES_BUFFLEN, sizeof(float) * model->_INDICES_BUFFLEN, model->_INDICES_BUFFLEN, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void SRE_ring1_Create_Full_Drawable(const char *shaders_path, const char *shape_path, const char *texture_path)
{
    // create a 3D Cube matrix object
    SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN] = SRE_ring1_Create_Model_Object(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    // create the default shader program
    SRE_ring1_Append_Model_Shader(SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN], shaders_path);
    SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_SELECTED_SHADER = 0;

    // create the 3D cube's shape (vertices, indices, GLBuffers, etc...)
    SRE_ring1_Append_Model_VerticesAndIndices(SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN], shape_path);

    // create the brick wall texture
    SRE_ring0_CreateTextureFromFile(texture_path, SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_Texture[SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_SELECTED_TEXTURE]);

    // get the uMVP uniform from our default OpenGL 3D Shader Program
    SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->mvpLoc = SRE_ring0_Get_Uniform_TransformationMatrix_From_ShaderProgram(SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_ShaderProgram[SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_SELECTED_SHADER]);

    // increment size counter
    SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN += 1;
}

void SRE_ring1_Delete_Full_Drawable(SRE_ring1_Model *drawable)
{
    // Log the destroyed model
    char logbuff[64];
    SRE_Log("Destroying model... at memory location: ", NULL);
    sprintf(logbuff, "%p", (void *)drawable);
    SRE_Log(logbuff, NULL);
    SRE_Log("\n", NULL);

    SRE_ring1_Destroy_Model_Object(drawable);
    SRE_Log("Drawable destroyed...\n", NULL);

    // clean up the list of drawables, do no let holes fit in the list
    SRE_Log("Clearing buffer from this drawable...\n", NULL);

    uint64_t reindexer = 0;
    for (uint64_t i = 0; i < _SRE_MAX_OBJs_LIST; i++)
    {
        if (SRE_Main_Stack->drawable_list[i] == drawable)
        {
            // Log that we found the drawable
            SRE_Log("Found destroyed model at index: ", NULL);
            sprintf(logbuff, "%lu", i);
            SRE_Log(logbuff, NULL);
            SRE_Log("\n", NULL);

            // reindexing process
            SRE_Log("Beginning reindexation process (if required)\n", NULL);
            for (reindexer = i+1; SRE_Main_Stack->drawable_list[reindexer] != NULL; reindexer++)
            {
                SRE_Main_Stack->drawable_list[reindexer-1] = SRE_Main_Stack->drawable_list[reindexer];
                
                SRE_Log("Reindexed drawable : ", NULL);
                sprintf(logbuff, "%p", (void *)SRE_Main_Stack->drawable_list[reindexer]);
                SRE_Log(logbuff, NULL);
                SRE_Log("\n", NULL);
            }
            break;
        }
    }
    SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN -= 1;
    SRE_Log("Fully deleted drawable properly.\n", NULL);
}


