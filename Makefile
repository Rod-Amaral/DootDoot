# Doot Doot by Rod build OOOO
CC=gcc

LFLAGS = -lSDL2 -lSDL2_mixer
CFLAGS = -c -w

win_LFLAGS = -lSDL2 -lSDL2_mixer
win_CFLAGS = -c -w

BIN_NAME = DootDoot

SOURCE_FILES =  $(BIN_NAME).c
OBJ_FILE = $(BIN_NAME).o

gnu/linux: $(BIN_NAME)

$(BIN_NAME): $(OBJ_FILE)
	$(CC) bin/$(OBJ_FILE)  $(LFLAGS) -o bin/$(BIN_NAME).bin
	
$(OBJ_FILE): src/$(SOURCE_FILES)
	$(CC) $(CFLAGS) src/$(SOURCE_FILES) -o bin/$(OBJ_FILE)

windows: win_$(BIN_NAME)

win_$(BIN_NAME) : win_$(OBJ_FILE)
	$(CC) -lmingw32 -lSDL2main bin\$(OBJ_FILE)  $(LFLAGS) -o bin\$(BIN_NAME).exe

win_$(OBJ_FILE): src\$(SOURCE_FILES)
	$(CC) $(CFLAGS) src\$(SOURCE_FILES) -o bin\$(OBJ_FILE)

clean:
	rm -rf bin/$(OBJ_FILE) bin/$(BIN_NAME).exe bin/$(BIN_NAME).bin