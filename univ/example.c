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
        }else
        {
            sprint = 1.0f;
        }
        if (keys[SDL_SCANCODE_W])
        {
            // cam forward
            SRE_Main_Stack->camera->zPos -= 0.05f * sprint;
            SRE_Main_Stack->camera->zLook -= 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_S])
        {
            // cam backward
            SRE_Main_Stack->camera->zPos += 0.05f * sprint;
            SRE_Main_Stack->camera->zLook += 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_A])
        {
            // cam left
            SRE_Main_Stack->camera->xPos -= 0.05f * sprint;
            SRE_Main_Stack->camera->xLook -= 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_D])
        {
            // cam right
            SRE_Main_Stack->camera->xPos += 0.05f * sprint;
            SRE_Main_Stack->camera->xLook += 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_LSHIFT])
        {
            // cam up
            SRE_Main_Stack->camera->yPos -= 0.05f * sprint;
            SRE_Main_Stack->camera->yLook -= 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_SPACE])
        {
            // cam down
            SRE_Main_Stack->camera->yPos += 0.05f * sprint;
            SRE_Main_Stack->camera->yLook += 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // check camera rotations
        if (keys[SDL_SCANCODE_LEFT])
        {
            SRE_Main_Stack->camera->yRotAngle -= 1.0f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            SRE_Main_Stack->camera->yRotAngle += 1.0f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            SRE_Main_Stack->camera->xRotAngle += 1.0f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            SRE_Main_Stack->camera->xRotAngle -= 1.0f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        SRE_ring1_Default_Draw_Update(500);
    }

    // MAIN LOOP





    // Proper exit...
    SRE_ring1_Exit_Engine();
    return 0;
}