Application: Simple program to play a sound file (pseudo) randomly with a minimum and maximum delay using SDL2

/*		Settings 		*/
The defines on _rodDoot_DootDoot.h in the src/ folder are used for the settings of the program


/*		Makefile		*/
To build executable for windows use:
make windows
(or) mingw32-make windows

To build on gnu/linux use:
make

To clean binary and .o files use:
make clean


/*		Build Requirements		*/
- gcc compiler 
- make (mingw32-make will do)
- SDL2 and SDL2_mixer



/*		How to Build on Windows 		*/
for a video tutorial (until the 12 minute mark) to how to get MinGW gcc and the SDL2 library files you can follow this tutorial:
https://youtu.be/UvJt9MZs_M8

the library files for SDL2mixer also need to be included like the SDL2 library files were included
(shown in the video)

Links for SDL2 and SDL2 Mixer:

SDL2
Get the MinGW Development library, SDL2-devel-x.x.x-mingw.tar.gz 
https://www.libsdl.org/download-2.0.php

SDL2 Mixer
Get the MinGW Development library,  SDL2_mixer-devel-x.x.x-mingw.tar.gz
https://www.libsdl.org/projects/SDL_mixer/

MinGW download link (if you need it):
https://osdn.net/projects/mingw/releases/68260

Once SDL2 and SDL2 library files are present, run make windows


/*		How to include the library files for SDL2 and SDL2_mixer in MinGW gcc		*/

Inside the unziped folders of SDL2 and SDL2 mixer, there should be one folder with the 32bit binaries and include files (i686-w64-mingw32 or something similar).

Inside the i686-w64-mingw32 folders, the bin, include, lib an share folders contain the libraries and include files we need.

For both the SDL and SDL mixer i686-w64-mingw32 folders, select and copy all these folders (bin include lib share folders), and paste them in the C:\MinGW folder.

The C:\MinGW folder contains its own (bin include lib and share) folders, and we are placing the files needed to compile with SDL2 and SDL2 mixer functionalities using MinGW gcc compiler.



/*		How to build on GNU/Linux 		*/
Depending on your distro, find out how to download SDL2 and SDL2_mixer libraries from the apt-repository of your distro

If you need more help checkout this link for SDL2 installation:
https://wiki.libsdl.org/Installation

just run make afterwards


/*		Media Files 		*/
You must include the media files in the same directory as the executable file or inside a media folder inside the directory where the executable is present.