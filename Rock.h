#ifndef __ROCKH__
#define __ROCKH__

#define BIGROCK 150
#define MEDROCK 100
#define SMLROCK 50

#include "GameObject.h"

class Rock : public GameObject
{
public:
    Rock(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n);

    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void render(SDL_Renderer *r);
    virtual void setExpl(const int& type);

    void setType(int type) { this->type = type; }
    int getType() { return type; }
private:
    int type;
    int num = 0;
    float angleVel = 0.0;
};

#endif