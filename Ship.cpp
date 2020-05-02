#include "Ship.h"

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
    if (thrust) {
        speed += 1;
        if (speed > 5) {
            speed = 5;
        }
        velocity[0] += speed * cosA;
        velocity[1] += speed * sinA;
    } else {
        speed = 0;
    }
    
    switch (rot) {
        case LEFT:
            angle -= 0.175;
            break;
        case RIGHT:
            angle += 0.175;
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
    cosA = cos(angle);
    sinA = sin(angle);
}

void Ship::render(SDL_Renderer *rend){
    texture = TextureManager::LoadTexture("img/ship.png", rend);
    SDL_RenderCopyEx(rend, texture, NULL, &position, angle, &center, SDL_FLIP_NONE);
}

