  
#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	// static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};