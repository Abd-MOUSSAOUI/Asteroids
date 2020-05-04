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
    void collisions();
    void rockShipCollision();
    void bulletRockCollision(Ship* player);
    void bulletShipCollision(Ship* player1, Ship* player2);
    void actionShip(const int& action, int playerNum, bool down);
    void updatePositions(const float& deltaTime);
    void interpolate(const float& deltaTime, const float& interpolation);
    void render(SDL_Renderer *rend);
    void setPlayerPos(const int& type);

    inline void setMultiSimple(const bool& val) { multiSimple = val; }
    inline void setMultiCombat(const bool& val) { multiCombat = val; }
    inline bool isMulti() { return (multiCombat || multiSimple); }
private:

    bool multiSimple = false;
    bool multiCombat = false;
    Ship player;
    Ship player2;
    std::map<int, Rock> rocks;
    int rockNum = 0;

    std::vector<Explosion*> explosions;

    std::string scoreP1, scoreP2;
    TTF_Font *font;
    SDL_Color White;
    SDL_Surface *surface_P1, *surface_P2;
    SDL_Texture *P1_t, *P2_t , *background;
    SDL_Rect p1_rect, p2_rect;
};