#ifndef RING2_H
#define RING2_H

#include "./univ.h"

#define CAM_MOVE_FORWARD 1
#define CAM_MOVE_BACKWARD 2
#define CAM_MOVE_LEFT 3
#define CAM_MOVE_RIGHT 4
#define CAM_ROTATE_UP 5
#define CAM_ROTATE_DOWN 6
#define CAM_ROTATE_LEFT 7
#define CAM_ROTATE_RIGHT 8
#define CAM_MOVE_UP 9
#define CAM_MOVE_DOWN 10



/* Mesh manipulation (a mesh is a complete animated "character" or "pnj" or playable "character" composed of multiple Drawables) */

typedef struct SRE_ring2_Mesh
{
    // local positions / rotations / scaling
    // _
    float xPos, yPos, zPos;
    float xRotAngle, yRotAngle, zRotAngle;
    float xScale, yScale, zScale;

    void (*update)(struct SRE_ring2_Mesh *self);
} SRE_ring2_Mesh;



/* ring 2 methods */

void _SRE_ring2_Mesh_do_Place_At(SRE_ring1_Model *self);



/* Mesh Manipulation */

void SRE_ring2_Make_Full_Mesh();



/* Camera Movement Routines */
void SRE_ring2_MoveCamera(const uint8_t cam_move_direction, float units);
void SRE_ring2_RotateCamera(const uint8_t cam_rotation_direction, float units);


#endif
