#ifndef RING1_H
#define RING1_H


#include "./univ.h"

/* GLOBAL VARIABLES */

#define _SRE_MAX_OBJ_VERTICES 128
#define _SRE_MAX_OBJ_INDICES 128
#define _SRE_MAX_GL_BUFFERS 8
#define _SRE_MAX_GL_TEXTURES 8
#define _SRE_MAX_GL_SHADERS 8
#define _SRE_MAX_GL_UNIFORMS 8
#define _SRE_MAX_OBJs_LIST 1024



/* Basic Engine setup functions */
// setup the basic necessary to start up the engine (setup SDL, GLAD, create window, context, etc...)
int SRE_ring1_Init_Engine(int depth_size, int multi_samples, int w_window, int h_window);
int SRE_ring1_Init_Drawing(float fov, float closest_distance, float farthest_distance);
void SRE_ring1_Exit_Engine();


/* Custom data types and "classes" */

// the rendering parameters
typedef struct SRE_ring1_Projection
{
    float fov; // use glm_rad() to convert to rads
    float hightScreen, widthScreen;
    float far, close;

    mat4 projection_matrix;

    void (*update)(struct SRE_ring1_Projection *self);
} SRE_ring1_Projection;
// the camera
typedef struct SRE_ring1_View
{
    float xPos, yPos, zPos;
    float xLook, yLook, zLook;
    float xTop, yTop, zTop;

    mat4 view_matrix;

    void (*update)(struct SRE_ring1_View *self);
} SRE_ring1_View;
// an object / caracter / whatever thing in the scene
typedef struct SRE_ring1_Model
{
    // local positions / rotations / scaling
    // _
    float xPos, yPos, zPos;
    float xRotAngle, yRotAngle, zRotAngle;
    float xScale, yScale, zScale;

    // CGLM matrix
    mat4 model_matrix;

    // OpenGL Low Level
    // _
    uint16_t _VERTICES_BUFFLEN;
    float *_VERTICES;
    uint16_t _INDICES_BUFFLEN;
    unsigned int *_INDICES;

    uint32_t _BUFFER_BUFFLEN;
    uint32_t _SELECTED_BUFFER;
    GLuint _VAO[_SRE_MAX_GL_BUFFERS];
    GLuint _VBO[_SRE_MAX_GL_BUFFERS];
    GLuint _EBO[_SRE_MAX_GL_BUFFERS];

    uint32_t _SHADER_PROGRAM_BUFFLEN;
    uint32_t _SELECTED_SHADER;
    GLuint _ShaderProgram[_SRE_MAX_GL_SHADERS];
    GLint mvpLoc;
    GLint uniforms[_SRE_MAX_GL_UNIFORMS];

    uint32_t _TEXTURE_BUFFLEN;
    uint32_t _SELECTED_TEXTURE;
    GLuint _Texture[_SRE_MAX_GL_TEXTURES];


    void (*update)(struct SRE_ring1_Model *self);
} SRE_ring1_Model;

/* Global Variable structure, main stack */
typedef struct SRE_Globals
{
    int w, h;
    SDL_Window *mainWindow;
    SDL_GLContext mainWindowGL_ctx;
    SRE_ring1_Projection *projection_context;
    SRE_ring1_View *camera;

    uint64_t _DRAWABLES_LIST_BUFFLEN;
    SRE_ring1_Model *drawable_list[_SRE_MAX_OBJs_LIST];
} SRE_Globals;

extern SRE_Globals *SRE_Main_Stack;


/* methods */

void SRE_ring1_Update_Transformation_Matrix(int mvpLoc, SRE_ring1_Model m, SRE_ring1_View v, SRE_ring1_Projection p);


// update 3D context Projection matrix
void _SRE_ring1_Projection_do_Set_Settings(SRE_ring1_Projection *self);
// place the camera by updating the View matrix
void _SRE_ring1_View_do_Place_At(SRE_ring1_View *self);
// place the object model by updating the Model matrix
void _SRE_ring1_Model_do_Place_At(SRE_ring1_Model *self);



/* Constructors */

SRE_ring1_Projection *SRE_ring1_Create_Projection_Object(float fov_degrees, float width_screen, float hight_screen, float close_distance, float far_distance);
SRE_ring1_View *SRE_ring1_Create_View_Object(float x_pos, float y_pos, float z_pos, float x_look, float y_look, float z_look, float x_top, float y_top, float z_top);
SRE_ring1_Model *SRE_ring1_Create_Model_Object(float x_pos, float y_pos, float z_pos, float x_rotation_angle_degrees, float y_rotation_angle_degrees, float z_rotation_angle_degrees, float x_scale, float y_scale, float z_scale);

void SRE_ring1_Destroy_Model_Object(SRE_ring1_Model *model);

// Append a shader to the shader buffer of an object, you can either use a path to a valid OpenGL Shading Language code (vertex and fragment shaders must be in the same directory !!), or the name of a default shader. DO NOT SPECIFY FILE EXTENTIONS !!
void SRE_ring1_Append_Model_Shader(SRE_ring1_Model *model, const char *shader_path);
// Append vertices and indices, also setup correctly the VAO and EBO (vertices and indices must be in the same directory !!). DO NOT SPECIFY FILE EXTENTIONS !!
void SRE_ring1_Append_Model_VerticesAndIndices(SRE_ring1_Model *model, const char *shape_path);

void SRE_ring1_Create_Full_Drawable(const char *shaders_path, const char *shape_path, const char *texture_path);

#endif
