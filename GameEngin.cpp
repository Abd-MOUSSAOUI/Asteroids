#include "GameEngin.h"
#include "TextureManager.h"
#include <iostream>

GameEngin::GameEngin() {}

GameEngin::GameEngin(SDL_Renderer *rend){
    player = Ship(rend);
}


void GameEngin::updatePositions(const float& deltaTime){
    player.updatePosition(deltaTime);

    // for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
    //     Rock& currentRock = rock->second;
    //     currentRock.updatePosition(deltaTime);
    // }
}
void GameEngin::render(SDL_Renderer *rend){
        SDL_Texture *background = TextureManager::LoadTexture("img/background.png", rend);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, background, 0, 0);
        player.render(rend);
        SDL_RenderPresent(rend);
}


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
            case GameEngin::FIRE:
                // if (player.isLoaded()) {
                //     player.fire();
                //     player.loaded(false);
                // }
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
        }
    }
}

void GameEngin::interpolate(const float& deltaTime, const float& interpolation){
    player.interpolate(deltaTime, interpolation);

    // for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
    //     Rock& currentRock = rock->second;
    //     currentRock.interpolate(deltaTime, interpolation);
    // }
}

