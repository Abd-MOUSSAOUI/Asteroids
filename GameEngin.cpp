#include "GameEngin.h"
#include "TextureManager.h"
#include "Ship.h"
#include <iostream>

GameEngin::GameEngin() {
    spawnRock(Rock::BIGROCK);
}

void GameEngin::actionShip(const int& action, int playerNum, bool down) {
    Ship* pl;
    if(playerNum == 1)
        pl = &player;
    else
        pl = &player2;
    
    if (down) {
        if (pl->isAlive()) {
            switch (action) {
            case GameEngin::UP:
                pl->thrusting(true);
                break;
            case GameEngin::LEFT:
                pl->rotate(Ship::LEFT);
                break;
            case GameEngin::RIGHT:
                pl->rotate(Ship::RIGHT);
                break;
            case GameEngin::FIRE:
                if (pl->isLoaded()) {
                    pl->fire();
                    pl->loaded(false);
                }
                break;
            default:
                break;
            }
        }
    } else {
        switch (action) {
        case GameEngin::UP:
            pl->thrusting(false);
            break;
        case GameEngin::LEFT:
            pl->rotate(Ship::NONE);
            break;
        case GameEngin::RIGHT:
            pl->rotate(Ship::NONE);
            break;
        case GameEngin::FIRE:
            pl->loaded(true);
            break;
        case GameEngin::ALIVE:
            pl->setAlive(true);
            break;
        default:
            break;
        }
    }
}

void GameEngin::spawnRock(const int& type, const float& x, const float& y)
{
    // if(rockNum >= 10)
    //     return;

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

void GameEngin::rockShipCollision() {
        SDL_Rect colPoint;
        for(auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& rk = rock->second;
        if(SDL_IntersectRect(player.getRect(), rk.getRect(), &colPoint) && player.isAlive()) {
            player.setAlive(false);
            player.setExpl(Explosion::SHIPEXPL);
            if(player.getLife() <= 1){
                player.setScore();
                player.setLife(3);
            } else {
                player.updateLife();
            }
        }

        if(SDL_IntersectRect(player2.getRect(), rk.getRect(), &colPoint) && player2.isAlive()) {
            player2.setAlive(false);
            player2.setExpl(Explosion::SHIPEXPL);
            if(player2.getLife() <= 1){
                player2.setScore();
                player2.setLife(3);
            } else {
                player2.updateLife();
            }
        }
    }
}

void GameEngin::bulletShipCollision(Ship* player1, Ship* player2) {
    SDL_Rect colPoint;
    for(auto bul = player1->getBullets()->begin(); bul != player1->getBullets()->end(); bul++) {
        Bullet& currbul = bul->second;
        if(SDL_IntersectRect(player2->getRect(), currbul.getRect(), &colPoint) && player2->isAlive()) {
            player2->setAlive(false);
            player2->setExpl(Explosion::SHIPEXPL);
            player2->updateLife();
            player1->addScoreCombat();
        }
    }
}

void GameEngin::bulletRockCollision(Ship* player) {
    SDL_Rect colPoint;
    bool col = true;
    while(col) {
    col = false;
    for (auto bul_it = player->getBullets()->begin(); bul_it != player->getBullets()->end(); bul_it++) {
        Bullet& bul = bul_it->second;
        for (auto rock_it = rocks.begin(); rock_it != rocks.end(); rock_it++) {
            Rock& rk = rock_it->second;
            if(SDL_IntersectRect(bul.getRect(), rk.getRect(), &colPoint)) {
                player->addScore();
                col = true;
                rockNum--;
                rocks.erase(rock_it);
                player->getBullets()->erase(bul_it++);

                if(rk.getType() == Rock::BIGROCK) {
                    spawnRock(Rock::MEDROCK, rk.getPosition().x-50, rk.getPosition().y);
                    spawnRock(Rock::MEDROCK, rk.getPosition().x+50, rk.getPosition().y);
                    //spawnRock(MEDROCK, rk.getPosition().x, rk.getPosition().y+50);
                    //spawnRock(SMLROCK, rk.getPosition().x, rk.getPosition().y);
                }
                if(rk.getType() == Rock::MEDROCK) {
                    //spawnRock(SMLROCK, rk.getPosition().x, rk.getPosition().y);
                    spawnRock(Rock::SMLROCK, rk.getPosition().x, rk.getPosition().y);
                    spawnRock(Rock::SMLROCK, rk.getPosition().x, rk.getPosition().y);
                }
                break;
            }
        }
        if(col)
            break;
        }
    }
}

void GameEngin::collisions() {
    rockShipCollision();
    bulletRockCollision(&player);
    if(isMulti())
        bulletRockCollision(&player2);
    if(multiCombat) {
        bulletShipCollision(&player, &player2);
        bulletShipCollision(&player2, &player);
    }

}

void GameEngin::updatePositions(const float& deltaTime){
    player.updatePosition(deltaTime);
    if(isMulti())
        player2.updatePosition(deltaTime);
    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.updatePosition(deltaTime);
    }
}

void GameEngin::interpolate(const float& deltaTime, const float& interpolation){
    player.interpolate(deltaTime, interpolation);
    if(isMulti())
        player2.interpolate(deltaTime, interpolation);
    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.interpolate(deltaTime, interpolation);
    }
}

void GameEngin::render(SDL_Renderer *rend){

        scoreP1 = "score: " + std::to_string(player.getScore()) + "    lives: " + std::to_string(player.getLife());               
        
        font = TTF_OpenFont("arial.ttf", 16);
        White = {255, 255, 255, 0};
        surface_P1 = TTF_RenderText_Solid(font, scoreP1.c_str(), White);
        P1_t = SDL_CreateTextureFromSurface(rend, surface_P1);
        p1_rect = {1000,0,180,50};  
        SDL_FreeSurface(surface_P1);
        if(isMulti()){
            scoreP2 = "score2: " + std::to_string(player2.getScore()) + "    lives: " + std::to_string(player2.getLife());
            surface_P2 = TTF_RenderText_Solid(font, scoreP2.c_str(), White);
            P2_t = SDL_CreateTextureFromSurface(rend, surface_P2);
            p2_rect = {0,0,180,50};  
            SDL_FreeSurface(surface_P2);
        }
        TTF_CloseFont(font);
        background = TextureManager::LoadTexture("img/background.png", rend);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, background, 0, 0);
        SDL_DestroyTexture(background);
        SDL_RenderCopy(rend, P1_t, NULL, &p1_rect); 
        SDL_DestroyTexture(P1_t);
        player.render(rend);
        if(isMulti()){
            SDL_RenderCopy(rend, P2_t, NULL, &p2_rect); 
            SDL_DestroyTexture(P2_t);
            player2.render(rend);
        }
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

void GameEngin::setPlayerPos(const int& type) {
    if(type == 1) {
        player.setInitPos(player.getRect()->x, player.getRect()->y-100);
        player2.setInitPos(player2.getRect()->x, player2.getRect()->y+100);
    } else {
        player.setInitPos(0, 50, 180);
        player2.setInitPos(1100, 700);
    }
}


