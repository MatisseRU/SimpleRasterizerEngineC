/*
    How does this engine works ?
    It is designed to be modular:
        -ring 0: OpenGL stuff (low level)
        -ring 1: Game Logic and OOP Objects (high level, designed to link your game and 3D operations easily, maybe GUI soon ?)
        -ring 2: Your game / your 2D/3D animation stuff / ressource editor which rely on ring 0 through ring 1 and also able to access ring 0 on its own.
*/

/* plateform independent includes */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL3/SDL.h>
#include "./glad.h"
#include <cglm/cglm.h>
#include <stdio.h>


// PROGRAMMING, REMOVED WHEN PUSHING
//#define PLATEFORM_LINUX 1
//#define PLATEFORM_WINDOWS 1
// PROGRAMMING, REMOVED WHEN PUSHING


#ifdef PLATEFORM_LINUX
    #undef PLATEFORM_WINDOWS
    #include "../platforms/Linux/linux.c"
#elif PLATEFORM_WINDOWS
    #undef PLATEFORM_LINUX
    #include "../platforms/Windows/windows.c"
#endif


// ring 0
/* OpenGL Shaders */

unsigned int SRE_CreateDefaultShaderProgram(void)
{
    /*
        Only requires to pass the xyz coordinates of the vertices to an OpenGL vec3 vertex attribute at layout location 0.
        I.E.:
        float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
        };

        unsigned int indices[] = {  // facultative
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // facultative: glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); <- the location 0
    */

    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";


    // OPENGL: create the Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource_default, NULL);
    glCompileShader(vertexShader);

    // OPENGL: create the Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource_default, NULL);
    glCompileShader(fragmentShader);

    // OPENGL: shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // OPENGL: clean up things and return the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
unsigned int SRE_CreateDefaultCornerColoredShaderProgram(void)
{
    /*
        Requires to pass the xyz coordinates and the respective color of each vertices to 2 OpenGL vec3 vertex attribute at layout location 0 for position and location 1 for color.
    */
    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   vertexColor = aColor;\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0);\n"
    "}\n\0";


    // OPENGL: create the Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource_default, NULL);
    glCompileShader(vertexShader);

    // OPENGL: create the Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource_default, NULL);
    glCompileShader(fragmentShader);

    // OPENGL: shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // OPENGL: clean up things and return the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
unsigned int SRE_3D_CreateDefaultCornerColoredShaderProgram(void)
{
    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform mat4 uMVP;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   vertexColor = aColor;\n"
    "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0);\n"
    "}\n\0";


    // OPENGL: create the Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource_default, NULL);
    glCompileShader(vertexShader);

    // OPENGL: create the Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource_default, NULL);
    glCompileShader(fragmentShader);

    // OPENGL: shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // OPENGL: clean up things and return the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// 3D related
int SRE_Get_Uniform_TransformationMatrix_From_ShaderProgram(unsigned int shaderProgram)
{
    return glGetUniformLocation(shaderProgram, "uMVP");
}


// ring 1
/* Custom data types and "classes" */

// the rendering parameters
typedef struct SRE_Projection
{
    float fov; // use glm_rad() to convert to rads
    float hightScreen, widthScreen;
    float far, close;

    mat4 projection_matrix;

    void (*update)(struct SRE_Projection *self);
} SRE_Projection;
// the camera
typedef struct SRE_View
{
    float xPos, yPos, zPos;
    float xLook, yLook, zLook;
    float xTop, yTop, zTop;

    mat4 view_matrix;

    void (*update)(struct SRE_View *self);
} SRE_View;
// an object / caracter / whatever thing in the scene
typedef struct SRE_Model
{
    float xPos, yPos, zPos;
    float xRotAngle, yRotAngle, zRotAngle;
    float xScale, yScale, zScale;

    mat4 model_matrix;

    void (*update)(struct SRE_Model *self);
} SRE_Model;


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

// constructors
SRE_Projection *SRE_Create_Projection_Object(float fov_degrees, float width_screen, float hight_screen, float close_distance, float far_distance)
{
    SRE_Projection* projection = malloc(sizeof(SRE_Projection));
    if(projection == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for object\n");
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
        fprintf(stderr, "Failed to allocate memory for object\n");
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
        fprintf(stderr, "Failed to allocate memory for object\n");
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

    return model;
}

