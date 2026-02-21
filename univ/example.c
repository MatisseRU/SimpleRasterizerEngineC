#include "./univ.h"


int main(int argc, char **argv)
{

    // DEBUG ?
    SRE_DEBUGGING = 1;
    // DEBUG ?


    if (SRE_ring1_Init_Engine(24, 2, 800, 600) < 0)
    {
        SRE_Log("Error while initialising engine\n", NULL);
        return -1;
    }

    // SRE_ring0_3D_ExportDefaultTexturedCube();

    // Initialize camera and projection context
    SRE_ring1_Init_Drawing(45.0f, 0.1f, 100.0f);


    // 3D cube with brick wall texture
    SRE_ring1_Create_Full_Drawable("./WADs/complete_models/3D_cube", "./WADs/complete_models/3D_cube", "./WADs/textures/wall.jpg");
    SRE_ring1_Create_Full_Drawable("./WADs/complete_models/3D_cube", "./WADs/complete_models/3D_cube", "./WADs/textures/wall.jpg");
    SRE_Main_Stack->drawable_list[0]->xPos = -2.0f;
    SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
    SRE_Main_Stack->drawable_list[1]->xPos = 2.0f;
    SRE_Main_Stack->drawable_list[1]->update(SRE_Main_Stack->drawable_list[1]);



    // MAIN LOOP

    SDL_Event ev;
    const bool *keys = SDL_GetKeyboardState(NULL);

    // amplifier (sprint camera)
    float sprint = 1.0f;

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

        // check camera movements
        if (keys[SDL_SCANCODE_LCTRL])
        {
            sprint = 2.0f; // sprint
        }
        else
        {
            sprint = 1.0f;
        }

        // Forward movement (W)
        if (keys[SDL_SCANCODE_W])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_FORWARD, 0.05f * sprint);
        }

        // Backward movement (S)
        if (keys[SDL_SCANCODE_S])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_BACKWARD, 0.05f * sprint);
        }

        // Left movement (A)
        if (keys[SDL_SCANCODE_A])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_LEFT, 0.05f * sprint);
        }

        // Right movement (D)
        if (keys[SDL_SCANCODE_D])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_RIGHT, 0.05f * sprint);
        }

        // DOWN movement (LSHIFT)
        if (keys[SDL_SCANCODE_LSHIFT])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_DOWN, 0.05f * sprint);
        }

        // UP movement (SPACE)
        if (keys[SDL_SCANCODE_SPACE])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_UP, 0.05f * sprint);
        }

        // check camera rotations
        if (keys[SDL_SCANCODE_LEFT])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_LEFT, 1.0f);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_RIGHT, 1.0f);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_UP, 1.0f);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_DOWN, 1.0f);
        }


        SRE_ring1_Default_Draw_Update(500);
    }

    // MAIN LOOP





    // Proper exit...
    SRE_ring1_Exit_Engine();
    return 0;
}