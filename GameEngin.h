#pragma once
#include "Ship.h"
#include "GameObject.h"
#include "Rock.h"

class GameEngin
{
public:

    enum action { UP = 0, LEFT = 1, RIGHT = 2, FIRE = 3, ALIVE = 4};
    GameEngin();

    void spawnRock(const int& type, const float& x = 0.0, const float& y = 0.0);
    void collisions(SDL_Renderer* rend);
    void actionShip(const int& action, bool down);
    void updatePositions(const float& deltaTime);
    void interpolate(const float& deltaTime, const float& interpolation);
    void render(SDL_Renderer *rend);


private:
    TTF_Font *font;
    SDL_Surface *surface;
    Ship player;
    std::map<int, Rock> rocks;
    int rockNum = 0;
};