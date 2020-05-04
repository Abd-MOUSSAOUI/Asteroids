  
#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};