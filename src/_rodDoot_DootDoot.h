#ifndef _RODDOOT_FUNCS_H
#define _RODDOOT_FUNCS_H

#include <stdio.h>
#include <pthread.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mixer.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <Windows.h>
#endif

/* Window Size */
#define WINDOW_X 150
#define WINDOW_Y 150

/* These set the maximum and minimum delay of a Doot Doot */
#define MAX_DELAY 20   /* in seconds */
#define MIN_DELAY 8    /* in seconds */

/* comment out defines to change settings */
#define _BOGGED_ /* Loading ze vectors Prints out Bogged onto terminal*/
/*#define _SMALL_BOGGED_ /* Smaller version of bogged. Doesn't work in all terminals*/
/*#define _TERMINAL_ /* If defined the terminal will be opened instead of the window */

typedef struct Window_wImage
{
    SDL_Window* Window;
    SDL_Surface* ScreenSurface;
    SDL_Surface* Image;
} _rodDoot_Window_wImage;


/* Initializing and Closing Function */
extern void _rodDoot_Window_wImage_Init(_rodDoot_Window_wImage* MainWindow);
extern Uint8 _rodDoot_Init(_rodDoot_Window_wImage* MainWindow, Mix_Chunk** Sound);
extern void _rodDoot_Close(_rodDoot_Window_wImage* MainWindow, Mix_Chunk** Sound);

#endif /* _RODDOOT_FUNCS_H */