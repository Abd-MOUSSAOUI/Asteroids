#ifndef __APPH__
#define __APPH__

#include "TextureManager.h"
#include "GameEngin.h"

class App {
    public:
        App(const char* title, int width, int height);
        GameEngin getGame() { return game;}
        void exit() { isRunning = false; }
        bool running() { return isRunning;}
        void eventsHandler();
        inline SDL_Renderer* getRend() { return renderer; }

    private:
        GameEngin game;
        bool isRunning = false;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif