#ifndef __ROCKH__
#define __ROCKH__

#include "GameObject.h"

class Rock : public GameObject
{
public:
    enum TYPES {
        BIGROCK = 150,
        MEDROCK = 100,
        SMLROCK = 50,
        LIFE = 52,
        SHOOT = 51
    };
    Rock(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n);

    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void render(SDL_Renderer *r);
    virtual void setExpl(const int& type);

    void setType(int type) { this->type = type; }
    int getType() { return type; }
    int getLife() {return life;}
private:
    int type;
    int num = 0;
    float angleVel = 0.0;
    int life = 30;
};

#endif