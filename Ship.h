#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Ship : public GameObject
{
public:
    enum rotateDir {LEFT = 1, RIGHT = 2, NONE = 0};

    Ship();
    
    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void render(SDL_Renderer *rend);
    virtual void setExpl(const int& type);
    
    void fire();
    
    inline void thrusting(bool val) { thrust = val; }
    inline void setAlive(const bool& val) { alive = val; }
    inline void loaded(const bool& val) { load = val; }
    inline void rotate(int val) { rot = val; }
    inline std::map<int, Bullet>* getBullets() { return &bullets; }
    inline bool isAlive() { return alive; }
    inline bool isLoaded() { return load; }
    inline void addScore() { score += 50; }
    inline void addScoreCombat() { score += 500; }
    inline int getScore() { return score; }
    inline void setScore() { score = 0; }
    inline void updateLife() { lifes -= 1; }
    inline int getLife() { return lifes; }
    inline void addLife() { lifes += 1; }
    inline void setLife(int val) { lifes = val; }
    inline void setShootMod(int val) { shootMod = val; }

private:
    std::map<int, Bullet> bullets;
    int rot = NONE;
    float speed = 0.0;
    int score = 0;
    bool alive = true;
    bool thrust = false;
    bool load = true;
    int lifes = 0;
    int bulletNum = 0;
    int shootMod = 1;
};
