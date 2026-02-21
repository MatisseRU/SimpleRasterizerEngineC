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


/* Camera Movement Routines */
void SRE_ring2_MoveCamera(const uint8_t cam_move_direction, float units);
void SRE_ring2_RotateCamera(const uint8_t cam_rotation_direction, float units);


#endif
