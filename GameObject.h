#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class GameObject
{
    public:
        enum action { UP = 0, LEFT = 1, RIGHT = 2, FIRE = 3, ALIVE = 4};

        void updatePosition(const float& dT);
        void interpolate(const float& dT, const float& i);        
        void render(SDL_Renderer *rend, const char* texture);
        SDL_Rect getRect();
        inline float* getVelocity() { return velocity; }
        inline SDL_Point getPosition() { return {position.x,position.y}; }
        void actionShip(const int& action);

    protected:
        float velocity[2];
        float cosA = 0.0;
        float sinA = 0.0;
        double angle = 0.0;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        SDL_Rect position, prevPosition;
        //SDL_Point center;
};