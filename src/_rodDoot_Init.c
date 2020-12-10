#include "_rodDoot_DootDoot.h"

void _rodDoot_Window_wImage_Init(_rodDoot_Window_wImage* MainWindow)
{
	MainWindow->Window = NULL;
	MainWindow->ScreenSurface = NULL;
	MainWindow->Image = NULL;
}

Uint8 _rodDoot_Init(_rodDoot_Window_wImage* MainWindow, Mix_Chunk** Sound)
{
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
            *Sound = Mix_LoadWAV("../media/doot_doot.wav");

            if(*Sound == NULL)
            	*Sound = Mix_LoadWAV("media/doot_doot.wav");

            if(*Sound == NULL)
            	*Sound = Mix_LoadWAV("doot_doot.wav");

            if(*Sound == NULL)
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

            	if(file == NULL)
            		file = fopen("media/small_bogged.txt", "r");

            	if(file == NULL)
            		file = fopen("small_bogged.txt", "r");
        	#else
            	FILE* file = fopen("../media/bogged.txt", "r");

            	if(file == NULL)
            		file = fopen("media/bogged.txt", "r");

            	if(file == NULL)
            		file = fopen("bogged.txt", "r");
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
        MainWindow->Window = SDL_CreateWindow( "Doot Doot", 0, 0, WINDOW_X, WINDOW_Y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(MainWindow->Window == NULL)
        {
          	printf( "Window was not created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
        else
        {
            MainWindow->ScreenSurface = SDL_GetWindowSurface(MainWindow->Window);

            MainWindow->Image = SDL_LoadBMP("../media/screen.bmp");

            if(MainWindow->Image == NULL)
            	MainWindow->Image = SDL_LoadBMP("media/screen.bmp");

            if(MainWindow->Image == NULL)
            	MainWindow->Image = SDL_LoadBMP("screen.bmp");

            if(MainWindow->Image == NULL)
            {
                printf( "Unable to load screen image! SDL Error: %s\n", SDL_GetError() );
                return 1;
            }
            else
            {
                SDL_BlitSurface(MainWindow->Image, NULL, MainWindow->ScreenSurface, NULL);
                SDL_UpdateWindowSurface(MainWindow->Window);
            }
        }
    }

    	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        	HWND windowHandle = GetConsoleWindow();
        	ShowWindow(windowHandle,SW_HIDE);
    	#endif

    #endif

    return 0;
}

void _rodDoot_Close(_rodDoot_Window_wImage* MainWindow, Mix_Chunk** Sound)
{
	SDL_FreeSurface(MainWindow->Image);
    MainWindow->Image = NULL;
    SDL_DestroyWindow(MainWindow->Window);
    MainWindow->Window = NULL;

    Mix_FreeChunk(*Sound);
    *Sound = NULL;

    Mix_Quit();
    SDL_Quit();
}