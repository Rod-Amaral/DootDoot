# Doot Doot by Rod build OOOO
CC=gcc

LFLAGS = -lSDL2 -lSDL2_mixer -lpthread
CFLAGS = -c -w

win_LFLAGS = -lSDL2 -lSDL2_mixer

BIN_NAME = DootDoot
MAIN_FILE = DootDoot.c

gnu/linux: bin/$(BIN_NAME).bin

bin/$(BIN_NAME).bin: bin/$(BIN_NAME).o
	$(CC) bin/$(BIN_NAME).o bin/_rodDoot_Init.o $(LFLAGS) -o bin/$(BIN_NAME).bin


windows: bin/$(BIN_NAME).exe

bin/$(BIN_NAME).exe: bin/$(BIN_NAME).o
	$(CC) -lmingw32 -lSDL2main bin/$(BIN_NAME).o bin/_rodDoot_Init.o $(win_LFLAGS) -o bin/$(BIN_NAME).exe


bin/$(BIN_NAME).o: bin/_rodDoot_Init.o
	$(CC) $(CFLAGS) src/$(MAIN_FILE) -o bin/$(BIN_NAME).o

bin/_rodDoot_Init.o:
	$(CC) $(CFLAGS) src/_rodDoot_Init.c -o bin/_rodDoot_Init.o

clean:
	rm -f bin/$(BIN_NAME).o bin/_rodDoot_Init.o bin/$(BIN_NAME).exe bin/$(BIN_NAME).bin

clean_build:
	rm -f bin/$(BIN_NAME).exe bin/$(BIN_NAME).bin