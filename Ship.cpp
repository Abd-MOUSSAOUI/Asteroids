#include "Ship.h"

Ship::Ship() {}

Ship::Ship(SDL_Renderer* rend)
{
    texture = TextureManager::LoadTexture("img/ship.png", rend);
    renderer = rend;
    prevPosition = {600, 400, 80, 80};
    position = {600, 400, 80, 80};
    velocity[0] = 0.0;
    velocity[1] = 0.0;
    //center = {position.w / 2, position.h / 2};
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
        case LEFT: {
            angle -= 0.175;
            break;
        }
        case RIGHT: {
            angle += 0.175;
            break;
        }
        case NONE: {
            break;
        }
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
    // for (auto i = bullets.begin(); i != bullets.end(); ) {
    //     if ((i -> second).isDead())
    //         i = bullets.erase(i);
    //     else
    //         ++i;
    // }
    // for (auto i = bullets.begin(); i != bullets.end(); i++) {
    //     i->second.updatePosition(dt, bullets);
    // }
    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Ship::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
    // std::cout << position.x << std::endl;
    // for (auto j = bullets.begin(); j != bullets.end(); j++)
    // {
    //     j->second.interpolate(dT, i);
    // }
}

void Ship::render(SDL_Renderer *rend){
    SDL_RenderCopyEx(rend, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE);
}


// void Ship::fire()
// {
//     SDL_Point p = baseFormula(coefArr[0][0], coefArr[0][1], coefArr[0][2], coefArr[0][3]);

//     float vX = velocity[0] + 500 * cosA;
//     float vY = velocity[1] + 500 * sinA;

//     std::stringstream ss;
//     ss << bulletNum;
//     std::string name = "bullet" + ss.str();

//     Bullet sp = {p, vX, vY, BULLET, bulletNum};

//     bullets.insert(std::pair<std::string, Bullet>(name, sp));
//     bulletNum++;
// }

// void Ship::deadAnimation()
// {
//     velocity[0] = 0;
//     velocity[1] = 0;
// }

