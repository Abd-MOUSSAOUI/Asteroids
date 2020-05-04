#include "Button.h"

Button::Button()
{   
    position = prevPosition = {600,250,200,50};
    center = {200/2,50/2};
}

void Button::render(SDL_Renderer *rend){
    texture = TextureManager::LoadTexture("src/start.png", rend);
    rendr = rend;
    SDL_RenderClear(rend);
    SDL_RenderCopyEx(rend, texture, NULL, &position, 0.0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(rend);
}

bool Button::isTriggered(int mouseX, int mouseY) {

    if(mouseX >= position.x && mouseX <= position.x + position.w && mouseY >= position.y && mouseY <= position.y + position.h) {
        pushedState = true;
        return true;
    }
    pushedState = false;
    return false;
}

void Button::update(const char* normal, const char* pushed) {
    
        if(pushedState) {
            if(!changed) {
                texture = TextureManager::LoadTexture(pushed, rendr);
                position.x += 1;
                position.y += 1;
                changed = true;
            }
        } else {
            if(changed) {
                texture = TextureManager::LoadTexture(normal, rendr);
                position.x -= 1;
                position.y -= 1;
                changed = false;
            }
        }

}