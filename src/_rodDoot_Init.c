#include "_rodDoot_DootDoot.h"

void _rodDoot_Window_wImage_Init(_rodDoot_Window_wImage* MainWindow)
{
	MainWindow->Window = NULL;
	MainWindow->ImageSurface = NULL;
	MainWindow->IconSurface = NULL;
	MainWindow->ImageTexture = NULL;
	MainWindow->Renderer = NULL;
}

Uint8 _rodDoot_Init(_rodDoot_Window_wImage* MainWindow, Mix_Chunk** Sound)
{
	/* Timer */
	if(SDL_Init(SDL_INIT_TIMER))
	{
		fprintf(stderr, "Unable to initialize SDL Timer: %s", SDL_GetError());
        return 1;
	}

    /* Audio */
	if (SDL_Init(SDL_INIT_AUDIO)) 
	{
        fprintf(stderr, "Unable to initialize SDL Audio: %s", SDL_GetError());
        return 1;
    }
    else
    {
        /* SDL Mixer init */
        if(Mix_OpenAudio( 22050 , MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
        {
            fprintf(stderr, "SDL_mixer could not be initialized! SDL Mixer Error: %s\n", Mix_GetError());
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
                fprintf(stderr, "Doot Doot sound affect could not be loaded! SDL Mixer Error: %s\n", Mix_GetError());
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
            fprintf(stderr, "Couldn't open bogged file!");

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
	    /* Video Init */
	    if(SDL_Init(SDL_INIT_VIDEO))
	    {
	        fprintf(stderr, "Unable to initialize SDL Video: %s\n", SDL_GetError() );
	        return 1;
	    }

	    /* Window Creation */
        MainWindow->Window = SDL_CreateWindow("Doot Doot", 0, 0, WINDOW_X, WINDOW_Y,
         SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(MainWindow->Window == NULL)
        {
          	fprintf(stderr, "Window was not created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
        
        /* Image Surface */
        MainWindow->ImageSurface = SDL_LoadBMP("../media/screen.bmp");

        if(MainWindow->ImageSurface == NULL)
        	MainWindow->ImageSurface = SDL_LoadBMP("media/screen.bmp");

        if(MainWindow->ImageSurface == NULL)
        	MainWindow->ImageSurface = SDL_LoadBMP("screen.bmp");

        if(MainWindow->ImageSurface == NULL)
        {
            fprintf(stderr, "Unable to load screen image! SDL Error: %s\n", SDL_GetError() );
            return 1;
        }

        MainWindow->Renderer = SDL_CreateRenderer(MainWindow->Window, -1, SDL_RENDERER_ACCELERATED);
        MainWindow->ImageTexture = SDL_CreateTextureFromSurface(MainWindow->Renderer, MainWindow->ImageSurface);
		SDL_RenderCopy(MainWindow->Renderer, MainWindow->ImageTexture, NULL, NULL);
		SDL_RenderPresent(MainWindow->Renderer);

        /* Set Window Icon */
        MainWindow->IconSurface = MainWindow->ImageSurface;
        SDL_SetWindowIcon(MainWindow->Window, MainWindow->IconSurface);

    	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    		/* Close Terminal window */
        	HWND windowHandle = GetConsoleWindow();
        	ShowWindow(windowHandle,SW_HIDE);
    	#endif

    #endif

    return 0;
}

void _rodDoot_Close(_rodDoot_Window_wImage* MainWindow, Mix_Chunk** Sound)
{
	#ifdef _DEBUG_
	fprintf(stderr, "Destroying Window\n");
	#endif
	SDL_DestroyWindow(MainWindow->Window);
    MainWindow->Window = NULL;

    #ifdef _DEBUG_
    fprintf(stderr, "Destroying ImageSurface\n");
    #endif
	SDL_FreeSurface(MainWindow->ImageSurface);
    MainWindow->ImageSurface = NULL;

    /*
    #ifdef _DEBUG_
    fprintf(stderr, "Destroying IconSurface\n");
    #endif
    SDL_FreeSurface(MainWindow->IconSurface);
    MainWindow->IconSurface = NULL;
    */

    #ifdef _DEBUG_
    fprintf(stderr, "Destroying ImageTexture\n");
    #endif
    SDL_DestroyTexture(MainWindow->ImageTexture);
    MainWindow->ImageTexture = NULL;

    #ifdef _DEBUG_
    fprintf(stderr, "Destroying Renderer\n");
    #endif
    SDL_DestroyRenderer(MainWindow->Renderer);
    MainWindow->Renderer = NULL;

	#ifdef _DEBUG_ 
	fprintf(stderr, "Destroying Sound\n");
	#endif
    Mix_FreeChunk(*Sound);
    *Sound = NULL;

    Mix_Quit();
    SDL_Quit();
}