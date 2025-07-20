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







    SDL_Quit();
    return 0;
}