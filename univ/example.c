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



    // MAIN LOOP

    SDL_Event ev;
    const bool *keys = SDL_GetKeyboardState(NULL);

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
        if (keys[SDL_SCANCODE_W])
        {
            // cam forward (zoom in)
            SRE_Main_Stack->camera->zPos -= 0.05f;
            SRE_Main_Stack->camera->zLook -= 0.05f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }
        if (keys[SDL_SCANCODE_S])
        {
            // cam backward (zoom out)
            SRE_Main_Stack->camera->zPos += 0.05f;
            SRE_Main_Stack->camera->zLook += 0.05f;
            SRE_Main_Stack->camera->update(SRE_Main_Stack->camera);
        }

        // check model movements
        if (keys[SDL_SCANCODE_LEFT])
        {
            SRE_Main_Stack->drawable_list[0]->yRotAngle += 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            SRE_Main_Stack->drawable_list[0]->yRotAngle -= 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }
        if (keys[SDL_SCANCODE_UP])
        {
            SRE_Main_Stack->drawable_list[0]->xRotAngle += 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            SRE_Main_Stack->drawable_list[0]->xRotAngle -= 1.0f;
            SRE_Main_Stack->drawable_list[0]->update(SRE_Main_Stack->drawable_list[0]);
        }

        SRE_ring1_Default_Draw_Update(500);
    }

    // MAIN LOOP





    // Proper exit...
    SRE_ring1_Exit_Engine();
    return 0;
}