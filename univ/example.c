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
            // cam forward
            // Calculate direction vector from camera position to look point (normalized)
            float dirX = SRE_Main_Stack->camera->xLook - SRE_Main_Stack->camera->xPos;
            float dirY = SRE_Main_Stack->camera->yLook - SRE_Main_Stack->camera->yPos;
            float dirZ = SRE_Main_Stack->camera->zLook - SRE_Main_Stack->camera->zPos;

            // Move camera along the direction vector
            SRE_Main_Stack->camera->xPos += dirX * 0.05f * sprint;
            SRE_Main_Stack->camera->yPos += dirY * 0.05f * sprint;
            SRE_Main_Stack->camera->zPos += dirZ * 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // Backward movement (S)
        if (keys[SDL_SCANCODE_S])
        {
            // cam backward
            float dirX = SRE_Main_Stack->camera->xPos - SRE_Main_Stack->camera->xLook;
            float dirY = SRE_Main_Stack->camera->yPos - SRE_Main_Stack->camera->yLook;
            float dirZ = SRE_Main_Stack->camera->zPos - SRE_Main_Stack->camera->zLook;

            SRE_Main_Stack->camera->xPos += dirX * 0.05f * sprint;
            SRE_Main_Stack->camera->yPos += dirY * 0.05f * sprint;
            SRE_Main_Stack->camera->zPos += dirZ * 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // Left movement (A)
        if (keys[SDL_SCANCODE_A])
        {
            // cam left
            // Calculate the right vector (perpendicular to the direction vector in the XZ plane)
            float dirX = SRE_Main_Stack->camera->zLook - SRE_Main_Stack->camera->zPos;
            float dirZ = -(SRE_Main_Stack->camera->xLook - SRE_Main_Stack->camera->xPos);

            SRE_Main_Stack->camera->xPos += dirX * 0.05f * sprint;
            SRE_Main_Stack->camera->zPos += dirZ * 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // Right movement (D)
        if (keys[SDL_SCANCODE_D])
        {
            // cam right
            float dirX = -(SRE_Main_Stack->camera->zLook - SRE_Main_Stack->camera->zPos);
            float dirZ = SRE_Main_Stack->camera->xLook - SRE_Main_Stack->camera->xPos;

            SRE_Main_Stack->camera->xPos += dirX * 0.05f * sprint;
            SRE_Main_Stack->camera->zPos += dirZ * 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // Up movement (LSHIFT)
        if (keys[SDL_SCANCODE_LSHIFT])
        {
            // cam up
            SRE_Main_Stack->camera->yPos -= 0.05f * sprint;
            SRE_Main_Stack->camera->yLook -= 0.05f * sprint;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // Down movement (SPACE)
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