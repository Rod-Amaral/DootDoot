# Doot Doot by Rod build OOOO
CC:=gcc

LFLAGS = -lSDL2
CFLAGS := -c -w

TARGET_NAME := DootDoot
OBJ_FILES := bin/DootDoot.o bin/_rodDoot_Init.o  bin/_rodDoot_ThreadFuncs.o bin/_rodDoot_Audio.o

DEPENDIES := $(patsubst %.o,%.d,$(OBJ_FILES))
-include $(DEPENDIES)
DEPFLAGS = -MMD -MF $(@:.o=.d)

gnu/linux: bin/$(TARGET_NAME).bin

bin/$(TARGET_NAME).bin: $(OBJ_FILES)
	$(CC) -lSDL2main $^ $(LFLAGS) -o $@


windows: bin/$(TARGET_NAME).exe

bin/$(TARGET_NAME).exe: $(OBJ_FILES)
	$(CC) -lmingw32 -lSDL2main $^ $(LFLAGS) -o $@


bin/%.o: src/%.c
	$(CC) $(CFLAGS) $< $(DEPGLAGS) -o $@


clean:
	rm -f $(OBJ_FILES) bin/$(TARGET_NAME).exe bin/$(TARGET_NAME).bin $(DEPENDIES)

clean_build:
	rm -f bin/$(TARGET_NAME).exe bin/$(TARGET_NAME).bin