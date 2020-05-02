#ifndef __APPH__
#define __APPH__

#include "TextureManager.h"
#include "GameEngin.h"

class App {
    public:
        App();
        void exit() { isRunning = false; }
        void eventsHandler();
        void exec();

    private:    
        SDL_Event event;
        GameEngin game;
        bool isRunning = true;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif