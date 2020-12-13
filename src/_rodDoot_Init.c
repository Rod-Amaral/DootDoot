#include "_rodDoot_DootDoot.h"

void _rodDoot_Window_wImage_Default(_rodDoot_Window_wImage* MainWindow)
{
	MainWindow->Window = NULL;
	MainWindow->ImageSurface = NULL;
	MainWindow->IconSurface = NULL;
	MainWindow->ImageTexture = NULL;
	MainWindow->Renderer = NULL;
}

void _rodDoot_SoundAndDevice_Default(_rodDoot_SoundAndDevice* SD)
{
	SD->Audio.Buffer = NULL;
	SD->Audio.Length = NULL;
	SD->WavBuffer = NULL;
	SD->WavLength = 0;
}

Uint8 _rodDoot_Init(_rodDoot_Window_wImage* MainWindow, _rodDoot_SoundAndDevice* SD)
{
	/* Audio */
	if(SDL_Init(SDL_INIT_AUDIO)) 
	{
        fprintf(stderr, "Unable to initialize SDL Audio: %s\n", SDL_GetError());
        return 1;
    }

	/* Timer */
	if(SDL_InitSubSystem(SDL_INIT_TIMER))
	{
		fprintf(stderr, "Unable to initialize SDL Timer: %s\n", SDL_GetError());
        return 1;
	}
    
    /* Load Doot Doot Sound */
	SDL_AudioSpec* TempSpec = NULL;

    TempSpec = SDL_LoadWAV("doot_doot.wav", &(SD->WavSpec), &(SD->WavBuffer), &(SD->WavLength));

    if(TempSpec == NULL)
    	TempSpec = SDL_LoadWAV("media/doot_doot.wav", &(SD->WavSpec), &(SD->WavBuffer), &(SD->WavLength));

    if(TempSpec == NULL)
    	TempSpec = SDL_LoadWAV("../doot_doot.wav", &(SD->WavSpec), &(SD->WavBuffer), &(SD->WavLength));

    if(TempSpec == NULL)
    	TempSpec = SDL_LoadWAV("../media/doot_doot.wav", &(SD->WavSpec), &(SD->WavBuffer), &(SD->WavLength));

    if(TempSpec == NULL)
    {
        fprintf(stderr, "Could not open Audio File! SDL Error: %s\n", SDL_GetError());
		return 1;
    }

    SD->Audio.Length = SD->WavLength;
	SD->Audio.Buffer = SD->WavBuffer;
	SD->WavSpec.callback = _rodDoot_AudioCallback;
	SD->WavSpec.userdata = &(SD->Audio);

	SD->AudioDevice = SDL_OpenAudioDevice(NULL, 0, &(SD->WavSpec), NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	if(SD->AudioDevice == 0)
	{
		fprintf(stderr, "Could not open Audio Device! SDL Error: %s\n", SDL_GetError());
		return 1;
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
            fprintf(stderr, "Couldn't open bogged file!\n");

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
	    if(SDL_InitSubSystem(SDL_INIT_VIDEO))
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

void _rodDoot_Close(_rodDoot_Window_wImage* MainWindow, _rodDoot_SoundAndDevice* SD)
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
    SDL_FreeWAV(SD->WavBuffer);
    SD->WavBuffer = NULL;
	SDL_CloseAudioDevice(SD->AudioDevice);

    SDL_Quit();
}