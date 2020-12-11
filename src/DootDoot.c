#include "_rodDoot_DootDoot.h"

int main(int argc, char** argv)
{
    /* Screen and Image */
    _rodDoot_Window_wImage MainWindow;
    _rodDoot_Window_wImage_Init(&MainWindow);

    /* Sound effect */
    Mix_Chunk* Sound = NULL;

    /* Events and Keyboard */
    const Uint8* state = SDL_GetKeyboardState(NULL);
    SDL_Event WindowEvent;

    /* Thread creation */
    SDL_Thread* threads[1];
    static SDL_mutex* Mutex;

    /* Thread Initialization */
    threads[1] = SDL_CreateThread(_rodDoot_RandoPlaySound, "Window", (void *) NULL);
    Mutex = SDL_CreateMutex();
    if(!Mutex) 
    {
        fprintf(stderr, "Couldn't create Mutex: %s\n", SDL_GetError());
        return 1;
    }

    /* Initialization */
    if(_rodDoot_Init(&MainWindow, &Sound))
    {
        SDL_DestroyMutex(Mutex);
        _rodDoot_Close(&MainWindow, &Sound);
        fprintf(stderr, "Initialization was not successful!\n");
        return 1;
    }

    /* Loooooooop */
    while(1)
    {   
        SDL_Delay(1);

        //#ifndef _TERMINAL_
            SDL_RenderClear(MainWindow.Renderer);
            SDL_RenderCopy(MainWindow.Renderer, MainWindow.ImageTexture, NULL, NULL);
            SDL_RenderPresent(MainWindow.Renderer);
        //#endif

        /* Check if a sound is to be played */
        if(!SDL_LockMutex(Mutex)) 
        {
            if(PLAY_SOUND)
            {
                PLAY_SOUND = 0;
                Mix_PlayChannel(-1, Sound, 0);
                #ifdef _DEBUG_
                    fprintf(stderr, "Doot Doot!\n");
                #endif
            }
            SDL_UnlockMutex(Mutex);
        }

        /* Close window if End key is pressed */
        if(state[SDL_SCANCODE_END])
            break;

        /* Close Window on Quit event */
        if(SDL_PollEvent(&WindowEvent))
            if(WindowEvent.type == SDL_QUIT)
                break;
    }

    #ifdef _DEBUG_
        puts("Closing Window!");
    #endif

    SDL_UnlockMutex(Mutex);
    SDL_DestroyMutex(Mutex);
    _rodDoot_Close(&MainWindow, &Sound);
	return 0;
}