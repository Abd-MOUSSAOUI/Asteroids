#include "Explosion.h"

Explosion::Explosion(const int& tp, const int& x, const int& y,const int& w, const int& h, const int& fw, const int& fh, const int & f) {
    position.x = x;
    position.y = y;
    position.h = h;
    position.w = w;
    textR = {0,0,fw,fh};
    frame = f;
    type = tp;
}

void Explosion::move() {
    delaycnt++;
    if(delaycnt >= 8) {
        delaycnt = 0;
        return;
    }

    if(active++ < frame)
        textR.x = active * textR.w;
}

void Explosion::render(SDL_Renderer* rend) {
    SDL_Texture* texture;
    if(type == SHIPEXPL)
        texture = TextureManager::LoadTexture("img/explosions/type_A.png", rend);
    if(type == ROCKEXPL)
        texture = TextureManager::LoadTexture("img/explosions/type_C.png", rend);
        
    SDL_RenderCopyEx(rend, texture, &textR, &position, rand()%360, 0, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
    this->move();
}