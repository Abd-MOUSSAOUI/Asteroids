#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    int FPS = 60;
    const int frameDelay = 1000 / FPS;
    uint32_t frameStrat;
    int frameTime;

	game = new Game();
	game->init("Asteroids", 1200, 800, false);

	while (game->running())
	{
        frameStrat = SDL_GetTicks();
        
		game->handleEvents();
		game->update();
		game->render();

        frameTime = SDL_GetTicks() - frameStrat;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
	}

	game->clean();
	return 0;
}