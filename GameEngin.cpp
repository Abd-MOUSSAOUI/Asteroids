#include "GameEngin.h"
#include "TextureManager.h"
#include "Ship.h"
#include <iostream>

GameEngin::GameEngin() {
    spawnRock(BIGROCK);
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
                if (player.isLoaded()) {
                    player.fire();
                    player.loaded(false);
                }
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
            player.loaded(true);
            break;
        case GameEngin::ALIVE:
            player.setAlive(true);
            break;
        default:
            break;
        }
    }
}

void GameEngin::spawnRock(const int& type, const float& x, const float& y)
{
    if(rockNum >= 10)
        return;

    SDL_Point tempPos;
    if (x == 0.0 && y == 00) {
        tempPos = {rand() % 1100 + 100, rand() % 700 + 100};
        if (tempPos.x < player.getPosition().x + 80 || tempPos.x > player.getPosition().x - 80 ||
            tempPos.y < player.getPosition().y + 80 || tempPos.y > player.getPosition().y - 80) {
            tempPos.x += 200;
            tempPos.y -= 200;
        }
    }
    
    tempPos = {int(x), int(y)};
    
    float tempVel[2];
    if (rand() % 2 + 1 == 2) {
        tempVel[0] = rand() % 25 + 15;
    } else {
        tempVel[0] = (rand()%25 + 15) * -1;
    }
    if (rand() % 2 + 1 == 2) {
        tempVel[1] = rand() % 25 + 15;
    } else {
        tempVel[1] = (rand() % 25 + 15) * -1;
    }

    Rock tempRock = {tempPos, tempVel[0], tempVel[1], type, rockNum};
    rocks.insert(std::pair<int, Rock>(rockNum, tempRock));
    rockNum++;
}

void GameEngin::collisions(SDL_Renderer* rend) {
    SDL_Rect colPoint;
    bool col = true;

    for(auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& rk = rock->second;
        if(SDL_IntersectRect(player.getRect(), rk.getRect(), &colPoint) && player.isAlive()) {
            player.setAlive(false);
            explosions.push_back(new Explosion(Explosion::SHIPEXPL, player.getRect()->x - (player.getRect()->w)/2, 
                                                                    player.getRect()->y - (player.getRect()->h)/2, 
                                                                    player.getRect()->w*1.5, 
                                                                    player.getRect()->h*1.5, 
                                                                    50, 50, 20));
            player.setScore();
        }
    }

    while(col) {
        std::cout << rockNum << std::endl;
        col = false;
        for (auto bul_it = player.getBullets()->begin(); bul_it != player.getBullets()->end(); bul_it++) {
            Bullet& bul = bul_it->second;
            for (auto rock_it = rocks.begin(); rock_it != rocks.end(); rock_it++) {
                Rock& rk = rock_it->second;
                if(SDL_IntersectRect(bul.getRect(), rk.getRect(), &colPoint)) {
                    player.addScore();
                    col = true;
                    rockNum--;
                    rocks.erase(rock_it);
                    player.getBullets()->erase(bul_it++);

                    if(rk.getType() == BIGROCK) {
                        spawnRock(MEDROCK, rk.getPosition().x-50, rk.getPosition().y);
                        spawnRock(MEDROCK, rk.getPosition().x+50, rk.getPosition().y);
                        spawnRock(MEDROCK, rk.getPosition().x, rk.getPosition().y+50);
                        spawnRock(SMLROCK, rk.getPosition().x, rk.getPosition().y);
                    }
                    if(rk.getType() == MEDROCK) {
                        spawnRock(SMLROCK, rk.getPosition().x, rk.getPosition().y);
                        spawnRock(SMLROCK, rk.getPosition().x, rk.getPosition().y);
                        spawnRock(SMLROCK, rk.getPosition().x, rk.getPosition().y);
                    }
                break;
                }
            }
            if(col)
                break;
        }
    }
}

void GameEngin::updatePositions(const float& deltaTime){
    player.updatePosition(deltaTime);
    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.updatePosition(deltaTime);
    }
}

void GameEngin::interpolate(const float& deltaTime, const float& interpolation){
    player.interpolate(deltaTime, interpolation);

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.interpolate(deltaTime, interpolation);
    }
}

void GameEngin::render(SDL_Renderer *rend){

        score_text = "score: " + std::to_string(player.getScore());        
        font = TTF_OpenFont("OpenSans-Regular.ttf", 10);
        White = {255, 255, 255, 0};  
        surface = TTF_RenderText_Solid(font, score_text.c_str(), White);
        TTF_CloseFont(font);
        score = SDL_CreateTextureFromSurface(rend, surface); 
        SDL_FreeSurface(surface);
        score_rect = {1000,0,150,50};  
        
        background = TextureManager::LoadTexture("img/background.png", rend);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, background, 0, 0);
        SDL_DestroyTexture(background);
        SDL_RenderCopy(rend, score, NULL, &score_rect); 
        SDL_DestroyTexture(score);
        player.render(rend);
        for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
            Rock& currentRock = rock->second;
            currentRock.render(rend);
        }
        int dead = true;
        while(dead) {
            dead = false;
            for (auto expl = explosions.begin(); expl != explosions.end(); expl++) {
                (*expl)->render(rend);
                if((*expl)->isActive() >= 20 ) {
                     expl = explosions.erase(expl);
                     dead = true;
                     break;
                }
            }
        }
        SDL_RenderPresent(rend);
}


