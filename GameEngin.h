#pragma once
#include "Game.h"

class GameEngin
{
    public:
        enum action { UP = 0, LEFT = 1, RIGHT = 2, FIRE = 3, ALIVE = 4};
        GameEngin(const char* textureSheet, SDL_Renderer* ren);
        ~GameEngin();

        void update();
        void render();
        void setSpeed(double sX);
        void setShow(bool s);
        double getSpeed();
        bool isShowing();
        void setRotation(double r);
        double getRotation();
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
        SDL_Rect getRect();
        bool isSimpleTexture();
        void setSimpleTexture(bool simpleTexture);
        void setDimensions(int w, int h);
        void setTexture(const char* textureSheet);
        void actionShip(const int& action);

    private:
        float velocity[2];
        float cosA = 0.0;
        float sinA = 0.0;
        double x = 0.0;
        double y = 0.0;
        double speed = 0.0;
        bool show = false;
        bool simpleTexture = false;
        double angle = 0.0;
        double rotation = 0.0;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        SDL_Rect position;
        SDL_Point center;
        int width = 60;
        int height = 60;
};