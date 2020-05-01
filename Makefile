OBJS = Game.cpp GameEngin.cpp TextureManager.cpp Vector2D.cpp main.cpp

CC = g++

COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = Asteroids

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm -rf Asteroids