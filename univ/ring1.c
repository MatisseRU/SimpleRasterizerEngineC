#include "./ring1.h"

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

