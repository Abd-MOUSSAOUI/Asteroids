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

    inline void setType(int type) { this->type = type; }
    inline int getType() { return type; }
    inline int getLife() {return life;}
private:
    int type;
    float angleVel = 0.0;
    int life = 45;
};

#endif