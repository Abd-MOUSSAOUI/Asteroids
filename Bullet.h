#pragma once
#include "GameObject.h"


class Bullet : public GameObject
{
public:
    enum bull { BULLET };
    Bullet(SDL_Rect r, const float& vX, const float& vY, const int& t, const int& n);
    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void render(SDL_Renderer *rend);
    bool isDead() const;

private:
    int type;
    bool dead;
};