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
    void thrusting(bool val) { thrust = val; }
    void setAlive(const bool& val) { alive = val; }
    void loaded(const bool& val) { load = val; }
    void rotate(int val) { rot = val; }
    std::map<int, Bullet>* getBullets() { return &bullets; }
    inline bool isAlive() { return alive; }
    inline bool isLoaded() { return load; }
    void addScore() { score += 50; }
    void addScoreCombat() { score += 500; }
    int getScore() { return score; }
    void setScore() { score = 0; }
    void updateLife() { lifes -= 1; }
    int getLife() { return lifes; }
    void addLife() { lifes += 1; }
    void setLife(int val) { lifes = val; }
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
};
