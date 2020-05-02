#pragma once
#include "Ship.h"
#include "GameObject.h"

class GameEngin
{
public:

    enum action { UP = 0, LEFT = 1, RIGHT = 2, FIRE = 3, ALIVE = 4};
    GameEngin();

    void actionShip(const int& action, bool down);
    void updatePositions(const float& deltaTime);
    void interpolate(const float& deltaTime, const float& interpolation);
    void render(SDL_Renderer *rend);

private:
    Ship player;
};