#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"

class Button
{
    public:
        Button();
        bool isTriggered(int mouseX, int mouseY);
        void update(const char* normal, const char* pushed);
        void render(SDL_Renderer *rend);
        
    private:

        SDL_Texture* texture;
        SDL_Rect position, prevPosition;
        SDL_Point center;
        SDL_Renderer* rendr;
        bool pushedState = false;
        bool changed = false;
};

#endif // BUTTON_H