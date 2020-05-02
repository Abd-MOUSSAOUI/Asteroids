#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include "GameObject.h"
#include "TextureManager.h"

class Ship : public GameObject
{
public:
    enum rotateDir {LEFT = 1, RIGHT = 2, NONE = 0};

    Ship();
    Ship(SDL_Renderer* rend);
    
    void updatePosition(const float& dT);
    void interpolate(const float& dT, const float& i);
    void render(SDL_Renderer *rend);

    //void fire();
    //void deadAnimation();

    void thrusting(const bool& val) { thrust = val; }
    void setAlive(const bool& val) { alive = val; }
    void loaded(const bool& val) { load = val; }
    void rotate(const int& val) { rot = val; }
    inline bool isAlive() { return alive; }
    inline bool isLoaded() { return load; }
    
private:

    int rot = NONE;
    float speed = 0.0;
    bool alive = true;
    bool thrust = false;
    bool load = true;
    //int bulletNum = 0;
};
