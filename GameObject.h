#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class GameObject
{
    public:
        virtual void updatePosition(const float& dT) = 0;
        virtual void interpolate(const float& dT, const float& i) = 0;        
        virtual void render(SDL_Renderer *rend) = 0;
        
        inline float* getVelocity() { return velocity; }
        inline SDL_Point getPosition() { return {position.x,position.y}; }

    protected:
        float velocity[2];
        float angle = 0.0;
        
        float cosA = 0.0;
        float sinA = 0.0;
        
        SDL_Texture* texture;
        SDL_Rect position, prevPosition;
        SDL_Point center;
};