# Doot Doot by Rod build OOOO
CC=gcc

LFLAGS = -lSDL2 -lSDL2_mixer
CFLAGS = -c -w

win_LFLAGS = -lSDL2 -lSDL2_mixer

BIN_NAME = DootDoot
OBJ_FILE = $(BIN_NAME).o

MAIN_FILE = DootDoot.c
SOURCE_FILES =

gnu/linux: bin/$(BIN_NAME).bin

bin/$(BIN_NAME).bin: bin/$(OBJ_FILE)
	$(CC) bin/$(OBJ_FILE)  $(LFLAGS) -o bin/$(BIN_NAME).bin


windows: bin/$(BIN_NAME).exe

bin/$(BIN_NAME).exe: bin/$(OBJ_FILE)
	$(CC) -lmingw32 -lSDL2main bin/$(OBJ_FILE) $(win_LFLAGS) -o bin/$(BIN_NAME).exe


bin/$(OBJ_FILE):
	$(CC) $(CFLAGS) src/$(SOURCE_FILES) src/$(MAIN_FILE) -o bin/$(OBJ_FILE)

clean:
	rm -rf bin/$(OBJ_FILE) bin/$(BIN_NAME).exe bin/$(BIN_NAME).bin