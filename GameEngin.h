#pragma once
#include "Ship.h"
#include "GameObject.h"

class GameEngin
{
public:

    enum action { UP = 0, LEFT = 1, RIGHT = 2, FIRE = 3, ALIVE = 4};
    GameEngin();
    GameEngin(SDL_Renderer *rend);

    //void spawnRock(const int& type, const int& number, const float& x = 0.0, const float& y = 0.0);

    void actionShip(const int& action, bool down);
    //void collisions();
    void updatePositions(const float& deltaTime);
    void interpolate(const float& deltaTime, const float& interpolation);
    void render(SDL_Renderer *rend);

private:
    Ship player;
    //std::map<std::string, Rock> rocks;
    //int rockNum = 0;
    
};