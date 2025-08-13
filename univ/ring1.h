#ifndef RING1_H
#define RING1_H


#include "./univ.h"




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

void SRE_Update_Transformation_Matrix(int mvpLoc, SRE_Model m, SRE_View v, SRE_Projection p);


// update 3D context Projection matrix
void _SRE_Projection_do_Set_Settings(SRE_Projection *self);
// place the camera by updating the View matrix
void _SRE_View_do_Place_At(SRE_View *self);
// place the object model by updating the Model matrix
void _SRE_Model_do_Place_At(SRE_Model *self);

// constructors
SRE_Projection *SRE_Create_Projection_Object(float fov_degrees, float width_screen, float hight_screen, float close_distance, float far_distance);
SRE_View *SRE_Create_View_Object(float x_pos, float y_pos, float z_pos, float x_look, float y_look, float z_look, float x_top, float y_top, float z_top);
SRE_Model *SRE_Create_Model_Object(float x_pos, float y_pos, float z_pos, float x_rotation_angle_degrees, float y_rotation_angle_degrees, float z_rotation_angle_degrees, float x_scale, float y_scale, float z_scale);

#endif
