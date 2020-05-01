#include "Game.h"
#include "TextureManager.h"
#include "GameEngin.h"

GameEngin *spaceship;
SDL_Texture *background;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	background = TextureManager::LoadTexture("img/background.png",renderer);
	spaceship = new GameEngin("img/ship.png",renderer);
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	case SDL_KEYDOWN:

		if (event.key.keysym.scancode == SDL_SCANCODE_UP ||
			event.key.keysym.scancode == SDL_SCANCODE_Z) {
			spaceship->actionShip(GameEngin::UP);
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
			event.key.keysym.scancode == SDL_SCANCODE_Q) {
			spaceship->actionShip(GameEngin::LEFT);
		} else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
				event.key.keysym.scancode == SDL_SCANCODE_D) {
			spaceship->actionShip(GameEngin::RIGHT);
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			spaceship->actionShip(GameEngin::FIRE);
		}

		break;

	case SDL_KEYUP:

		if (event.key.keysym.scancode == SDL_SCANCODE_UP ||
			event.key.keysym.scancode == SDL_SCANCODE_Z) {
			spaceship->actionShip(GameEngin::UP);
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
			event.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
			event.key.keysym.scancode == SDL_SCANCODE_Q ||
			event.key.keysym.scancode == SDL_SCANCODE_D) {
			//
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_R) {
			//
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			//
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	spaceship->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	spaceship->render();
	//SDL_RenderCopyEx(renderer, ship, nullptr, &position, angle, &center, flip);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}