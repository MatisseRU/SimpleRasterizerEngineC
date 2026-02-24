#include "./ring2.h"

void SRE_ring2_MoveCamera(const uint8_t cam_move_direction, float units)
{
    if (cam_move_direction == CAM_MOVE_FORWARD)
    {
        // cam forward
        // Calculate direction vector from camera position to look point (normalized)
        float dirX = SRE_Main_Stack->camera->xLook - SRE_Main_Stack->camera->xPos;
        float dirY = SRE_Main_Stack->camera->yLook - SRE_Main_Stack->camera->yPos;
        float dirZ = SRE_Main_Stack->camera->zLook - SRE_Main_Stack->camera->zPos;

        // Move camera along the direction vector
        SRE_Main_Stack->camera->xPos += dirX * units;
        SRE_Main_Stack->camera->yPos += dirY * units;
        SRE_Main_Stack->camera->zPos += dirZ * units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }

    // Backward movement
    if (cam_move_direction == CAM_MOVE_BACKWARD)
    {
        // cam backward
        float dirX = SRE_Main_Stack->camera->xPos - SRE_Main_Stack->camera->xLook;
        float dirY = SRE_Main_Stack->camera->yPos - SRE_Main_Stack->camera->yLook;
        float dirZ = SRE_Main_Stack->camera->zPos - SRE_Main_Stack->camera->zLook;

        SRE_Main_Stack->camera->xPos += dirX * units;
        SRE_Main_Stack->camera->yPos += dirY * units;
        SRE_Main_Stack->camera->zPos += dirZ * units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }

    // Left movement
    if (cam_move_direction == CAM_MOVE_LEFT)
    {
        // cam left
        // Calculate the right vector (perpendicular to the direction vector in the XZ plane)
        float dirX = SRE_Main_Stack->camera->zLook - SRE_Main_Stack->camera->zPos;
        float dirZ = -(SRE_Main_Stack->camera->xLook - SRE_Main_Stack->camera->xPos);

        SRE_Main_Stack->camera->xPos += dirX * units;
        SRE_Main_Stack->camera->zPos += dirZ * units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }

    // Right movement
    if (cam_move_direction == CAM_MOVE_RIGHT)
    {
        // cam right
        float dirX = -(SRE_Main_Stack->camera->zLook - SRE_Main_Stack->camera->zPos);
        float dirZ = SRE_Main_Stack->camera->xLook - SRE_Main_Stack->camera->xPos;

        SRE_Main_Stack->camera->xPos += dirX * units;
        SRE_Main_Stack->camera->zPos += dirZ * units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
    // Down movement
    if (cam_move_direction == CAM_MOVE_DOWN)
    {
        // cam up
        SRE_Main_Stack->camera->yPos -= units;
        SRE_Main_Stack->camera->yLook -= units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
    // Up movement
    if (cam_move_direction == CAM_MOVE_UP)
    {
        // cam down
        SRE_Main_Stack->camera->yPos += units;
        SRE_Main_Stack->camera->yLook += units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
}
void SRE_ring2_RotateCamera(const uint8_t cam_rotation_direction, float units)
{
    if (cam_rotation_direction == CAM_ROTATE_LEFT)
    {
        SRE_Main_Stack->camera->yRotAngle -= units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
    if (cam_rotation_direction == CAM_ROTATE_RIGHT)
    {
        SRE_Main_Stack->camera->yRotAngle += units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
    if (cam_rotation_direction == CAM_ROTATE_UP)
    {
        SRE_Main_Stack->camera->xRotAngle += units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
    if (cam_rotation_direction == CAM_ROTATE_DOWN)
    {
        SRE_Main_Stack->camera->xRotAngle -= units;
        SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
    }
}

void SRE_ring2_Create_Full_Grey_Floor(void)
{
    SRE_Log("[ring 1] Starting to Create Full Grey Floor...\n", NULL);
    // create a 3D Cube matrix object
    SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN] = SRE_ring1_Create_Model_Object(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    // create the default shader program
    SRE_ring1_Append_Model_Shader(SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN], "./WADs/scene_editor/models/x_floor");
    SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_SELECTED_SHADER = 0;

    // create the 3D cube's shape (vertices, indices, GLBuffers, etc...)
    SRE_ring1_Append_Model_VerticesAndIndices(SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN], "./WADs/scene_editor/models/x_floor");

    // get the uMVP uniform from our default OpenGL 3D Shader Program
    SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->mvpLoc = SRE_ring0_Get_Uniform_TransformationMatrix_From_ShaderProgram(SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_ShaderProgram[SRE_Main_Stack->drawable_list[SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN]->_SELECTED_SHADER]);

    // increment size counter
    SRE_Main_Stack->_DRAWABLES_LIST_BUFFLEN += 1;

    SRE_Log("[ring 1] Exiting Create Full Grey Floor.\n", NULL);
}
