#include "_rodDoot_DootDoot.h"

int main(int argc, char** argv)
{
    /* Screen and Image */
    _rodDoot_Window_wImage MainWindow;
    _rodDoot_Window_wImage_Default(&MainWindow);

    /* Sound */
    _rodDoot_SoundAndDevice SD;
    _rodDoot_SoundAndDevice_Default(&SD);

    /* Events and Keyboard */
    const Uint8* state = SDL_GetKeyboardState(NULL);
    SDL_Event WindowEvent;

    /* Thread creation */
    SDL_Thread* threads[1];
    static SDL_mutex* Mutex;

    /* Thread Initialization */
    threads[1] = SDL_CreateThread((void*)_rodDoot_RandoPlaySound, "Window", (void *) NULL);
    Mutex = SDL_CreateMutex();
    if(!Mutex) 
    {
        fprintf(stderr, "Couldn't create Mutex: %s\n", SDL_GetError());
        return 1;
    }

    /* Initialization */
    if(_rodDoot_Init(&MainWindow, &SD))
    {
        SDL_DestroyMutex(Mutex);
        _rodDoot_Close(&MainWindow, &SD);
        fprintf(stderr, "Initialization was not successful!\n");
        return 1;
    }

    /* Loooooooop */
    while(1)
    {   
        //SDL_Delay(1);

        #ifndef _TERMINAL_
            SDL_RenderClear(MainWindow.Renderer);
            SDL_RenderCopy(MainWindow.Renderer, MainWindow.ImageTexture, NULL, NULL);
            SDL_RenderPresent(MainWindow.Renderer);
        #endif

        /* Check if a sound is to be played */
        if(!SDL_LockMutex(Mutex)) 
        {
            if(PLAY_SOUND)
            {
                PLAY_SOUND = 0;
                SDL_PauseAudioDevice(SD.AudioDevice, 0);
                #ifdef _DEBUG_
                    fprintf(stderr, "Doot Doot!\n");
                #endif
            }
            SDL_UnlockMutex(Mutex);
        }

        if(!(SD.Audio.Length > 0))
        {
            SDL_PauseAudioDevice(SD.AudioDevice, 1);
            SD.Audio.Length = SD.WavLength;
            SD.Audio.Buffer = SD.WavBuffer;
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
    _rodDoot_Close(&MainWindow, &SD);
	return 0;
}