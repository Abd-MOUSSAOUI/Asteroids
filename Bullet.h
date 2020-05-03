#pragma once

#include <iostream>
#include <string>
#include <map>

#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet();
    ~Bullet();

    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void render(SDL_Renderer *rend);
    bool isDead() const;
    
private:
    int life = 0;
    int num = 0;
    int rNum = 0;
    int type;
    bool dead;
};