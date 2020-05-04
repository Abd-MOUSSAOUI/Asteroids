#include "App.h"
#include <cassert>

App::App() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow("Asteroid", 
                                  SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, 
                                  1200, 
                                  800, 
                                  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
        TTF_Init();
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		assert(renderer !=nullptr);
	}
}

void App::eventsHandler() {
    
    while (SDL_PollEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            this->exit();
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                SDL_Event focus;
                focus.type = SDL_WINDOWEVENT;
                focus.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
                SDL_WaitEvent(&focus);
            }
        }
        switch(event.type) {

            case SDL_MOUSEBUTTONDOWN:
                    int x, y;
                    SDL_GetMouseState( &x, &y );
                    if(start.isTriggered(x, y)) {
                        startPushed = true;
                        std::cout << x << " " << y << std::endl;
                    }
            break;

            case SDL_KEYDOWN:

                if (event.key.keysym.scancode == SDL_SCANCODE_UP ||
                    event.key.keysym.scancode == SDL_SCANCODE_Z)
                    game.actionShip(GameEngin::UP, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                    event.key.keysym.scancode == SDL_SCANCODE_Q)
                    game.actionShip(GameEngin::LEFT, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
                    event.key.keysym.scancode == SDL_SCANCODE_D)
                    game.actionShip(GameEngin::RIGHT, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    game.actionShip(GameEngin::FIRE, true);
                break;

            case SDL_KEYUP:

                if (event.key.keysym.scancode == SDL_SCANCODE_UP ||
                    event.key.keysym.scancode == SDL_SCANCODE_Z)
                    game.actionShip(GameEngin::UP, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                    event.key.keysym.scancode == SDL_SCANCODE_Q)
                    game.actionShip(GameEngin::LEFT, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
                    event.key.keysym.scancode == SDL_SCANCODE_D)
                    game.actionShip(GameEngin::RIGHT, false);
                    
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    game.actionShip(GameEngin::FIRE, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_R) 
                    game.actionShip(GameEngin::ALIVE, false);
                break;
            default:
                break;
        }
    }
}

void App::exec() {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int prevFrame = 0;
    int nextFrame = SDL_GetTicks();
    srand(time(NULL));
    float dt = 0;
    float interpolation = 0;
    float rockTimer = 0;

    // start.render(renderer);
    // while(!startPushed){
    //     this->eventsHandler();
    // }

    while(isRunning) {

        if(SDL_GetTicks() > rockTimer + 4000) {
            game.spawnRock(BIGROCK);
            rockTimer = SDL_GetTicks();
        }
        this->eventsHandler();
        dt = float(SDL_GetTicks() - prevFrame)/ 1000.0f;
        int count = 0;

        while (SDL_GetTicks() > nextFrame && count < 5) {
            game.updatePositions(dt);
            nextFrame += frameDelay;
            prevFrame = SDL_GetTicks();
            count++;
        }
        game.collisions(renderer);
        interpolation = float(SDL_GetTicks() + frameDelay - nextFrame) / float(frameDelay);
        game.interpolate(dt, interpolation);
        game.render(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

int main(){
    App app;
    app.exec();
    return 0;
}