#include "Bullet.h"

Bullet::Bullet(SDL_Rect r, const float& vX, const float& vY, const int& t, const int& n)
{
    if (type == BULLET) {
    }
    prevPosition = {r.x, r.y, 10, 10};
    position = {r.x, r.y, 10, 10};
    velocity[0] = vX;
    velocity[1] = vY;
    center = {position.w / 2, position.h / 2};
}


void Bullet::updatePosition(const float& dt)
{
    cosA = cos(angle*M_PI/180);
    sinA = sin(angle*M_PI/180);

    position.x = prevPosition.x - velocity[0] * dt;
    position.y = prevPosition.y - velocity[1] * dt;

    if (position.x > 1200 || position.x < 0 || position.y > 800 || position.y < 0) 
        dead = true; 

    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Bullet::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
}

void Bullet::render(SDL_Renderer *rend){
    SDL_Rect dest = {position.x+40, position.y+40, 10, 10};
    texture = TextureManager::LoadTexture("img/bullet.png", rend);
    SDL_RenderCopyEx(rend, texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
}

bool Bullet::isDead() const
{
    return dead;
}
