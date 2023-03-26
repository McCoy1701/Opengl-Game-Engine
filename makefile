CC=gcc
CFLAGS=-lglut -lGL -lGLU -lm

SRC_DIR=src
ENGINE_DIR=engine
BIN_DIR=bin
OBJ_DIR=obj

.PHONY: all clean


all: $(BIN_DIR)


$(BIN_DIR): $(OBJ_DIR)/main.o $(OBJ_DIR)/input.o $(OBJ_DIR)/render.o $(OBJ_DIR)/renderInit.o $(OBJ_DIR)/time.o
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/input.o $(OBJ_DIR)/render.o $(OBJ_DIR)/renderInit.o $(OBJ_DIR)/time.o -o $(BIN_DIR)/$@ $(CFLAGS)


$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/input.o: $(ENGINE_DIR)/input/input.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/render.o: $(ENGINE_DIR)/render/render.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/renderInit.o: $(ENGINE_DIR)/render/renderInit.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/time.o: $(ENGINE_DIR)/time/time.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -r $(OBJ_DIR) $(BIN_DIR)
