// PROGRAMMING, REMOVED WHEN PUSHING
#define PLATEFORM_LINUX 1
// PROGRAMMING, REMOVED WHEN PUSHING


#ifdef PLATEFORM_LINUX
    #undef PLATEFORM_WINDOWS
    #include "../platforms/Linux/linux.c"
#elif PLATEFORM_WINDOWS
    #undef PLATEFORM_LINUX
    #include "../plateforms/windows/windows.c"
#endif


int main(int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Failed at SDL_Init: \n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }else
    {
        printf("Initialised SDL, version: %d\n", SDL_GetVersion());
    }


    SDL_Window *mainWindow = SDL_CreateWindow("Main Test", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (mainWindow == NULL)
    {
        fprintf(stderr, "Failed at SDL_CreateWindow: \n%s\n", SDL_GetError());
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }

    SDL_GLContext mainWindowGL_ctx = SDL_GL_CreateContext(mainWindow);
    if (mainWindowGL_ctx == NULL)
    {
        fprintf(stderr, "Failed at SDL_GL_CreateContext: \n%s\n", SDL_GetError());
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }









    

    uint8_t run = 1;
    SDL_Event ev;
    while (run)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_EVENT_QUIT)
            {
                run = 0;
            }
        }

        SDL_Delay(100);
    }




    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}