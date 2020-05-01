#include "GameEngin.h"
#include "TextureManager.h"
#include <iostream>

GameEngin::GameEngin(const char* textureSheet, SDL_Renderer* ren)
{
    renderer = ren;
    texture = TextureManager::LoadTexture(textureSheet, ren);
    velocity[0] = 0.0;
    velocity[1] = 0.0;
}

void GameEngin::update() {

    SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h); // Récupere la dimension de la texture
    cosA = cos(angle);
    sinA = sin(angle);
    position.x = (1200 / 2 - position.w / 2) + speed;
	position.y = (800 / 2 - position.h / 2) + speed;

	center = { position.w / 2, position.h / 2 };
	if (angle < 0)
		angle = 360;
	if (angle > 360)
		angle = 0;
}

void GameEngin::render() {
    SDL_RenderCopyEx(renderer, texture, NULL, &position, angle, &center, SDL_FLIP_NONE);
}

void GameEngin::actionShip(const int& action)
{
    switch (action) {
        case GameEngin::UP:
            speed +=1;
            // if (speed > 5) {
            //     speed = 5;
            // }
            velocity[0] += speed * cosA;
            velocity[1] += speed * sinA;
            break;
        case GameEngin::LEFT:
            angle -= 0.175;
            break;
        case GameEngin::RIGHT:
            angle += 0.175;
            break;
        case GameEngin::FIRE:
            // 
            break;
        case GameEngin::ALIVE:
            // 
        break;
    }
    position.x -= velocity[0];
    position.y -= velocity[1];

    if (position.x > 1200) {
        position.x = 0;
    }
    if (position.x < 0) {
        position.x = 1200;
    }
    if (position.y > 800) {
        position.y = 0;
    }
    if (position.y < 0) {
        position.y = 800;
    }
}

void GameEngin::setSpeed(double uX) {
    this->speed = uX;
}

void GameEngin::setRotation(double r) {
    this->rotation += r;
}

void GameEngin::setShow(bool s) {
    this->show = s;
}

double GameEngin::getSpeed() {
    return this->speed;
}


double GameEngin::getRotation() {
    return this->rotation;
}

bool GameEngin::isShowing() {
    return this->show;
}

double GameEngin::getX() {
    return x;
}

double GameEngin::getY() {
    return y;
}

void GameEngin::setX(double x) {
    this->x = x;
}

void GameEngin::setY(double y) {
    this->y = y;
}

SDL_Rect GameEngin::getRect() {
    return this->position;
}

bool GameEngin::isSimpleTexture() {
    return this->simpleTexture;
}

void GameEngin::setSimpleTexture(bool s) {
    this->simpleTexture = s;
}

void GameEngin::setDimensions(int w, int h) {
    width = w;
    height = h;
}

void GameEngin::setTexture(const char* textureSheet) {
    this->texture = TextureManager::LoadTexture(textureSheet, renderer);
}