#include "Rock.h"

Rock::Rock(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n)
: type(t), num(n)
{   
    position = {p.x, p.y, t, t};
    prevPosition = {p.x, p.y, t, t};
    angle = (rand() % 314) / 100;
    if (num % 2 == 0) {
        angleVel = 0.01;
    } else {
        angleVel = -0.01;
    }

    velocity[0] = vX;
    velocity[1] = vY;
}

void Rock::updatePosition(const float& dT)
{
    position.x = prevPosition.x - velocity[0] * dT;
    position.y = prevPosition.y - velocity[1] * dT;

    if (position.x > 1200) {
        position.x -= 1200;
    } 
    
    if (position.x < 0) {
        position.x += 1200;
    }
    
    if (position.y > 800) {
        position.y -= 800;
    }
    
    if (position.y < 0) {
        position.y += 800;
    }
    
    angle += angleVel;

    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Rock::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
}

void Rock::render(SDL_Renderer* rend)
{
    texture = TextureManager::LoadTexture("img/asteroid.png", rend);
    SDL_RenderCopyEx(rend, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
}