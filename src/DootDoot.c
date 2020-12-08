#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mixer.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <Windows.h>
#endif

/* These set the maximum and minimum delay of a Doot Doot */
#define MAX_DELAY 20   /* in seconds */
#define MIN_DELAY 8    /* in seconds */

/* comment out defines to change settings */
/*#define _BOGGED_ /* Loading ze vectors Prints out Bogged onto terminal*/
/*#define _SMALL_BOGGED_ /* Smaller version of bogged. Doesn't work in all terminals*/
#define _TERMINAL_ /* If defined the terminal will be opened instead of the window */ 

int main(int argc, char** argv)
{
    /* Doot Doot Sound effect */
    Mix_Chunk *DootDoot = NULL;

    /* Screen and Image */
    SDL_Window* Window = NULL;
    SDL_Surface* ScreenSurface = NULL;
    SDL_Surface* Image = NULL;

    /* Audio */
	if (SDL_Init(SDL_INIT_AUDIO)) 
	{
        printf("Unable to initialize SDL Audio: %s", SDL_GetError());
        return 1;
    }
    else
    {
        /* SDL Mixer init */
        if( Mix_OpenAudio( 22050 , MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf("SDL_mixer could not be initialized! SDL Mixer Error: %s\n", Mix_GetError());
            return 1;
        }
        else
        {
            /* Load Doot Doot Sound */
            DootDoot = Mix_LoadWAV("../media/doot_doot.wav");
            if(DootDoot == NULL)
            {
                printf("Doot Doot sound affect could not be loaded! SDL Mixer Error: %s\n", Mix_GetError());
                return 1;
            }
        }
    }

    #ifdef _TERMINAL_
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
    #else
    /* Screen Image */
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        printf( "Unable to initialize SDL Video: %s\n", SDL_GetError() );
        return 1;
    }
    else
    {
        Window = SDL_CreateWindow( "Doot Doot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 150, 150, SDL_WINDOW_SHOWN );
        if(Window == NULL)
        {
          printf( "Window was not created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
        else
        {
            ScreenSurface = SDL_GetWindowSurface(Window);

            Image = SDL_LoadBMP("../media/screen.bmp");
            if(Image == NULL)
            {
                printf( "Unable to load screen image! SDL Error: %s\n", SDL_GetError() );
                return 1;
            }
            else
            {
                SDL_BlitSurface(Image, NULL, ScreenSurface, NULL);
                SDL_UpdateWindowSurface(Window);
            }
        }
    }

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        HWND windowHandle = GetConsoleWindow();
        ShowWindow(windowHandle,SW_HIDE);
    #endif

    #endif

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    time_t t;

    /* Intializes random number generator with new seed*/
    srand((unsigned) time(&t));

    /* OOOO DOOT DOOT */
    while(1) 
    {
        SDL_Delay( ((rand()%(MAX_DELAY-MIN_DELAY))+MIN_DELAY) * 1000 );
        Mix_PlayChannel( -1, DootDoot, 0 );
        SDL_UpdateWindowSurface(Window);
        if (state[SDL_SCANCODE_CUT])
            break;
    }

    SDL_FreeSurface(Image);
    Image = NULL;
    SDL_DestroyWindow(Window);
    Window = NULL;

    Mix_FreeChunk(DootDoot);
    DootDoot = NULL;

    Mix_Quit();
    SDL_Quit();

	return 0;
}