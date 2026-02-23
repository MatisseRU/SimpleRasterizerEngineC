#include "./univ.h"






int main(int argc, char **argv)
{

    // DEBUG ?
    if (argc > 1)
    {
        if (!strcmp(argv[1], "--debug"))
        {
            SRE_DEBUGGING = 1;
            printf("\nENABLED DEBUGGING\n");
        }
    }
    // DEBUG ?

    // Initialize core engine
    if (SRE_ring1_Init_Engine(24, 2, 800, 600) < 0)
    {
        SRE_Log("Error at init engine\n", NULL);
        return -1;
    }
    // Initialize camera and projection context
    if (SRE_ring1_Init_Drawing(45.0f, 0.1f, 100.0f) < 0)
    {
        SRE_Log("Error at init drawing\n", NULL);
        return -1;
    }


    // big (0;0;0) center-cross drawable
    SRE_ring1_Create_Full_Drawable("./WADs/scene_editor/models/central_cross","./WADs/scene_editor/models/central_cross_x","./WADs/scene_editor/textures/Red.jpg");
    SRE_ring1_Create_Full_Drawable("./WADs/scene_editor/models/central_cross", "./WADs/scene_editor/models/central_cross_y", "./WADs/scene_editor/textures/Green.jpeg");
    SRE_ring1_Create_Full_Drawable("./WADs/scene_editor/models/central_cross", "./WADs/scene_editor/models/central_cross_z", "./WADs/scene_editor/textures/Blue.jpeg");


    // MAIN LOOP

    SDL_Event ev;
    const bool *keys = SDL_GetKeyboardState(NULL);

    // amplifier (sprint camera)
    float sprint = 2.0f;

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
            SRE_ring2_MoveCamera(CAM_MOVE_FORWARD, 0.01f * sprint);
        }

        // Backward movement (S)
        if (keys[SDL_SCANCODE_S])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_BACKWARD, 0.01f * sprint);
        }

        // Left movement (A)
        if (keys[SDL_SCANCODE_A])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_LEFT, 0.01f * sprint);
        }

        // Right movement (D)
        if (keys[SDL_SCANCODE_D])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_RIGHT, 0.01f * sprint);
        }

        // DOWN movement (LSHIFT)
        if (keys[SDL_SCANCODE_LSHIFT])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_DOWN, 0.01f * sprint);
        }

        // UP movement (SPACE)
        if (keys[SDL_SCANCODE_SPACE])
        {
            SRE_ring2_MoveCamera(CAM_MOVE_UP, 0.01f * sprint);
        }

        // check camera rotations
        if (keys[SDL_SCANCODE_LEFT])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_LEFT, 0.25f * sprint);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_RIGHT, 0.25f * sprint);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_UP, 0.25f * sprint);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            SRE_ring2_RotateCamera(CAM_ROTATE_DOWN, 0.25f * sprint);
        }


        SRE_ring1_Default_Draw_Update(60);
    }

    // MAIN LOOP




    SRE_ring1_Exit_Engine();
    return 0;
}