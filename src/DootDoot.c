#include "_rodDoot_DootDoot.h"

volatile Uint8 DO_WINDOW = 1;

void _rodDoot_UpdateWindow(void* MainWindow)
{
    while(1)
    {
        SDL_UpdateWindowSurface(((_rodDoot_Window_wImage*) MainWindow)->Window);
        SDL_Delay(1);
    }
}

int main(int argc, char** argv)
{
    /* Screen and Image */
    _rodDoot_Window_wImage MainWindow;
    _rodDoot_Window_wImage_Init(&MainWindow);

    /* Sound effect */
    Mix_Chunk* Sound = NULL;

    int rc = 0;

    if(_rodDoot_Init(&MainWindow, &Sound))
    {
        _rodDoot_Close(&MainWindow, &Sound);
        return 1;
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    time_t t;

    /* Intializes random number generator with new seed */
    srand((unsigned) time(&t));

    pthread_t threads[1];

    rc = pthread_create(&threads[0], NULL, _rodDoot_UpdateWindow,(void *) &MainWindow);
    if(rc)
        printf("ERROR; return code from pthread_create() is %i\n", rc); 

    /* OOOO DOOT DOOT */
    while(1) 
    {
        SDL_Delay( ((rand()%(MAX_DELAY-MIN_DELAY))+MIN_DELAY) * 1000 );
        Mix_PlayChannel( -1, Sound, 0 );
        if (state[SDL_SCANCODE_CUT])
        {
            DO_WINDOW = 0;
            break;
        }
    }

    _rodDoot_Close(&MainWindow, &Sound);
	return 0;
}