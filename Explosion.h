#pragma once

#include "TextureManager.h"
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 

class Explosion {
    public:
        enum explosionType { SHIPEXPL = 0, ROCKEXPL = 1};
        Explosion(const int& tp, const int& x, const int& y, const int& w, const int& h, const int& fw, const int& fh, const int& f);
        void move();
        void render(SDL_Renderer* rend);
        inline int isActive() {return active; }
    private:
        SDL_Rect position;
        SDL_Rect textR;
        int delaycnt = 0;
        int active = 0;
        int frame = 0;
        int type;
};