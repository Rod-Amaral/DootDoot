#include "_rodDoot_DootDoot.h"

volatile Uint8 PLAY_SOUND = 0;

Uint8 _rodDoot_RandoPlaySound(void* not)
{
    #ifdef _DEBUG_ 
        puts("Sound Thread working"); 
    #endif

    static SDL_mutex* mutex;
    time_t t;
    mutex = SDL_CreateMutex();

    if(mutex == NULL) 
    {
        fprintf(stderr, "Couldn't create mutex: %s\n", SDL_GetError());
        return 1;
    }

    /* Intializes random number generator with new seed */
    srand((unsigned) time(&t));

    while(1)
    {
        SDL_Delay(((rand()%(MAX_DELAY-MIN_DELAY))+MIN_DELAY) * 1000);

        while(SDL_LockMutex(mutex)) {} 
        PLAY_SOUND = 1;
        SDL_UnlockMutex(mutex);
    }
    SDL_DestroyMutex(mutex);

    #ifdef _DEBUG_
        puts("Sound Thread Closed");
    #endif

    return 0;
}