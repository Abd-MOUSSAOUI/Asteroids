#include "Ship.h"

Ship::Ship()
{
    prevPosition = {600, 400, 80, 80};
    position = {600, 400, 80, 80};
    velocity[0] = 0.0;
    velocity[1] = 0.0;
    lifes = 3;
    center = {position.w / 2, position.h / 2};
}


void Ship::updatePosition(const float& dt)
{
    cosA = cos(angle*M_PI/180);
    sinA = sin(angle*M_PI/180);
    if (thrust) {
        speed = 2;
        velocity[0] += speed * cosA;
        velocity[1] += speed * sinA;
    } else {
        speed = 0;
    }
    switch (rot) {
        case LEFT:
            angle -= 5;
            break;
        case RIGHT:
            angle += 5;
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
    for (auto i = bullets.begin(); i != bullets.end(); ) {
        if ((i -> second).isDead())
            i = bullets.erase(i);
        else
            ++i;
    }
    for (auto i = bullets.begin(); i != bullets.end(); i++) {
        i->second.updatePosition(dt);
    }

    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Ship::fire()
{
    cosA = cos(angle*M_PI/180);
    sinA = sin(angle*M_PI/180);
    velocity[0] += speed * cosA;
    velocity[1] += speed * sinA;

    SDL_Rect r = {position.x, position.y, 10, 10};
    float vX = velocity[0] + 150 * cosA;
    float vY = velocity[1] + 150 * sinA;

    Bullet sp = {r, vX, vY, Bullet::BULLET, bulletNum};
    bullets.insert(std::pair<int, Bullet>(bulletNum, sp));
    bulletNum++;
}

void Ship::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
    if(alive){
        cosA = cos(angle*M_PI/180);
        sinA = sin(angle*M_PI/180);
    } else {
        velocity[0] = velocity[1] = 0;
    }
    for (auto j = bullets.begin(); j != bullets.end(); j++)
    {
        j->second.interpolate(dT, i);
    }
}

void Ship::render(SDL_Renderer *rend){

    if(alive){
        texture = TextureManager::LoadTexture("img/ship.png", rend);
        SDL_RenderCopyEx(rend, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
    }

    if(expl != nullptr) {
        expl->render(rend);
        if(!expl->isActive())
            expl = nullptr;
    }
    
    for (auto i = bullets.begin(); i != bullets.end(); i++) {
        i->second.render(rend);
    }
}

void Ship::setExpl(const int& type) {
    expl = new Explosion(type, position.x - position.w/2, 
                                              position.y - position.h/2, 
                                              position.w*1.5, 
                                              position.h*1.5, 
                                              50, 50, 20);
}
