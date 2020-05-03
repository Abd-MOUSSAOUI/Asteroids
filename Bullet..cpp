#include "Bullet.h"

Ship::Ship()
{
    prevPosition = {600, 400, 80, 80};
    position = {600, 400, 80, 80};
    velocity[0] = 0.0;
    velocity[1] = 0.0;
    center = {position.w / 2, position.h / 2};
}


void Ship::updatePosition(const float& dt)
{
    cosA = cos(angle*M_PI/180);
    sinA = sin(angle*M_PI/180);
    speed = 10;
    velocity[0] += speed * cosA;
    velocity[1] += speed * sinA;
    
    switch (rot) {
        case LEFT:
            angle -= 2.5;
            break;
        case RIGHT:
            angle += 2.5;
            break;
        case NONE:
            break;
        default:
            break;
    }

    position.x = prevPosition.x - velocity[0] * dt;
    position.y = prevPosition.y - velocity[1] * dt;

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

    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Ship::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
}

void Ship::render(SDL_Renderer *rend){

    texture = TextureManager::LoadTexture("img/ship.png", rend);
    SDL_RenderCopyEx(rend, texture, NULL, &position, angle, &center, SDL_FLIP_NONE);
}

bool Bullet::isDead() const
{
    return dead;
}
