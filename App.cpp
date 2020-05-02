#include "App.h"
#include <cassert>

App::App(const char* title, int width, int height) {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, 
                                  SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, 
                                  width, 
                                  height, 
                                  SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		assert(renderer !=nullptr);
		isRunning = true;
        game = GameEngin(renderer);
	}
}

void App::eventsHandler() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:

                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			        game.actionShip(GameEngin::UP, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    game.actionShip(GameEngin::LEFT, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    game.actionShip(GameEngin::RIGHT, true);
                
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    // game.actionShip(GameEngin::FIRE, true);
                
                break;
            case SDL_KEYUP:

                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			        game.actionShip(GameEngin::UP, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			        game.actionShip(GameEngin::LEFT, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			        game.actionShip(GameEngin::RIGHT, false);
                
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    // game.actionShip(GameEngin::FIRE, false);
                
                break;
            default:
                break;
        }
    }
}

int main(int argc, char** argv) {

    App app = App("Asteroid", 1200, 800);
    GameEngin game = app.getGame();

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int prevFrame = 0;
    int nextFrame = SDL_GetTicks();
    float dt = 0;
    float interpolation = 0;

    while(app.running()) {
        app.eventsHandler();
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
        game.render(app.getRend());
    } 
    SDL_Quit();
}