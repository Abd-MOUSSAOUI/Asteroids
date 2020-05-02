#include "GameEngin.h"
#include "TextureManager.h"
#include "Ship.h"
#include <iostream>

GameEngin::GameEngin() {}

void GameEngin::actionShip(const int& action,  bool down) {
    if (down) {
        if (player.isAlive()) {
            switch (action) {
            case GameEngin::UP:
                player.thrusting(true);
                break;
            case GameEngin::LEFT:
                player.rotate(Ship::LEFT);
                break;
            case GameEngin::RIGHT:
                player.rotate(Ship::RIGHT);
                break;
            default:
                break;
            }
        }
    } else {
        switch (action) {
        case GameEngin::UP:
            player.thrusting(false);
            break;
        case GameEngin::LEFT:
            player.rotate(Ship::NONE);
            break;
        case GameEngin::RIGHT:
            player.rotate(Ship::NONE);
            break;
        case GameEngin::FIRE:
            //player.loaded(true);
            break;
        case GameEngin::ALIVE:
            player.setAlive(true);
            break;
        default:
            break;
        }
    }
}

void GameEngin::updatePositions(const float& deltaTime){
    player.updatePosition(deltaTime);
}

void GameEngin::interpolate(const float& deltaTime, const float& interpolation){
    player.interpolate(deltaTime, interpolation);
}

void GameEngin::render(SDL_Renderer *rend){
        SDL_Texture *background = TextureManager::LoadTexture("img/background.png", rend);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, background, 0, 0);
        player.render(rend);
        SDL_RenderPresent(rend);
}


