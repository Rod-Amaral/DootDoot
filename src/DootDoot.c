#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mixer.h>


/* These set the maximum and minimum delay of a Doot Doot */
#define MAX_DELAY 20   /* in seconds */
#define MIN_DELAY 8    /* in seconds */

/* comment out _BOGGED_ to remove bogged print :( */
#define _BOGGED_ /* Loading ze vectors */
/* #define _SMALL_BOGGED_ /* Smaller version of bogged. Doesn't work in all terminals*/

int main(int argc, char** argv)
{ 
	if (SDL_Init(SDL_INIT_AUDIO) != 0) 
	{
        SDL_LogError("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

	/* Doot Doot Sound effect */
	Mix_Chunk *DootDoot = NULL;


	/* SDL Mixer init */
    if( Mix_OpenAudio( 22050 , MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
       	SDL_LogError("SDL_mixer could not be initialized! SDL Mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    /* Load Doot Doot Sound */
    DootDoot = Mix_LoadWAV( "../media/doot_doot.wav"  );
    if( DootDoot == NULL )
    {
        SDL_LogError("Doot Doot sound affect could not be loaded! SDL Mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    time_t t;

    /* Intializes random number generator with new seed*/
    srand((unsigned) time(&t));

    #ifdef _BOGGED_
        #ifdef _SMALL_BOGGED_
            FILE* file = fopen("../media/small_bogged.txt", "r");
        #else
            FILE* file = fopen("../media/bogged.txt", "r");
        #endif

        if(file == NULL)
            puts("Couldn't open bogged file!");

        long long int char_limit, char_count;
        char_limit = 10000;
        char_count = 0;

        char c = fgetc(file);
        while(c != EOF && (char_count <= char_limit) )
        {
            char_count++;
            putchar(c);
            c = fgetc(file);
        }
        fclose(file);

        puts("\nLoading ze vectors");
    #endif

    /* OOOO DOOT DOOT */
    while(1) 
    {
        SDL_Delay( ((rand()%(MAX_DELAY-MIN_DELAY))+MIN_DELAY) * 1000 );
        Mix_PlayChannel( -1, DootDoot, 0 );
        if (state[SDL_SCANCODE_CUT])
            break;
    }

    Mix_FreeChunk(DootDoot);
    Mix_Quit();
    SDL_Quit();

	return 0;
}