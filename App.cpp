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

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		assert(renderer !=nullptr);
	}
}

void App::eventsHandler() {
    
    while (SDL_PollEvent(&event)) {

        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
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
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    game.actionShip(GameEngin::FIRE, false);
            }
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

    while(isRunning) {
        this->eventsHandler();
        dt = float(SDL_GetTicks() - prevFrame)/ 1000.0f;
        int count = 0;

        while (SDL_GetTicks() > nextFrame && count < 5) {
            game.updatePositions(dt);
            nextFrame += frameDelay;
            prevFrame = SDL_GetTicks();
            count++;
        }
        interpolation = float(SDL_GetTicks() + frameDelay - nextFrame) / float(frameDelay);
        game.interpolate(dt, interpolation);
        game.render(renderer);
    }
    SDL_Quit();
}

int main(){
    App app;
    app.exec();
    return 0;
}