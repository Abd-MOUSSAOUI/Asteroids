#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "TextureManager.h"


class GameObject
{
    public:
        virtual void updatePosition(const float& dT) = 0;
        virtual void interpolate(const float& dT, const float& i) = 0;        
        virtual void render(SDL_Renderer *rend) = 0;
        
        inline float* getVelocity() { return velocity; }
        inline SDL_Point getPosition() { return {position.x, position.y}; }
        inline SDL_Rect* getRect() { return &position; }

    protected:
        float velocity[2];
        float angle = 0.0;
        
        float cosA = 0.0;
        float sinA = 0.0;
        
        SDL_Texture* texture;
        SDL_Rect position, prevPosition;
        SDL_Point center;
};