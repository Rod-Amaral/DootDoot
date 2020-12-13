#ifndef _RODDOOT_FUNCS_H
#define _RODDOOT_FUNCS_H

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mutex.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <Windows.h>
#endif

/*****		Settings 		*****/

/* Window Size */
#define WINDOW_X 150
#define WINDOW_Y 150

/* These set the maximum and minimum delay of a Doot Doot */
#define MAX_DELAY 10   /* in seconds */
#define MIN_DELAY 5    /* in seconds */

/* comment out defines to change settings */
/*#define _TERMINAL_ /* If defined the terminal will be opened instead of the window */
/*#define _BOGGED_ /* Loading ze vectors Prints out Bogged onto terminal*/
/*#define _SMALL_BOGGED_ /* Smaller version of bogged. Doesn't work in all terminals*/
#define _DEBUG_ /* Enables some Debug messages */

/*****		End of Settings 		*****/

/* Flag Variables */
extern volatile Uint8 PLAY_SOUND;

typedef struct Window_wImage
{
    SDL_Window* Window;
    SDL_Surface* ImageSurface;
    SDL_Surface* IconSurface;
    SDL_Texture* ImageTexture;
    SDL_Renderer* Renderer;
} _rodDoot_Window_wImage;


typedef struct structAudioData
{
	Uint8* Buffer;
	Uint32 Length;
}_rodDoot_AudioData;


typedef struct structSoundAndDevice
{
	_rodDoot_AudioData Audio;

	Uint8* WavBuffer;
	Uint32 WavLength;
	SDL_AudioSpec WavSpec;
	SDL_AudioDeviceID AudioDevice;
}_rodDoot_SoundAndDevice;

/* Init Functions */
extern void _rodDoot_Window_wImage_Init(_rodDoot_Window_wImage* MainWindow);
extern Uint8 _rodDoot_Init(_rodDoot_Window_wImage* MainWindow, _rodDoot_SoundAndDevice* SD);
extern void _rodDoot_Close(_rodDoot_Window_wImage* MainWindow, _rodDoot_SoundAndDevice* SD);

/* ThreadFuncs Functions */
extern Uint8 _rodDoot_RandoPlaySound(void* not);

/* Audio Function */
extern void _rodDoot_AudioCallback(void* Userdata, Uint8* Stream, int StreamLength);

#endif /* _RODDOOT_FUNCS_H */