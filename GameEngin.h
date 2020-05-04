#pragma once
#include "Ship.h"
#include "GameObject.h"
#include "Rock.h"
#include "Explosion.h"

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
    Ship player;
    std::map<int, Rock> rocks;
    int rockNum = 0;

    std::vector<Explosion*> explosions;

    std::string score_text;
    TTF_Font *font;
    SDL_Color White;
    SDL_Surface *surface;
    SDL_Texture *score , *background;
    SDL_Rect score_rect;
};