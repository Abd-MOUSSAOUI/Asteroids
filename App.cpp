#include "App.h"

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

            case SDL_KEYDOWN:

                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                    game.actionShip(GameEngin::UP, 1, true);

                if(event.key.keysym.scancode == SDL_SCANCODE_Z && game.isMulti())
                    game.actionShip(GameEngin::UP, 2, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    game.actionShip(GameEngin::LEFT, 1, true);
                
                if(event.key.keysym.scancode == SDL_SCANCODE_Q && game.isMulti() )
                    game.actionShip(GameEngin::LEFT, 2, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    game.actionShip(GameEngin::RIGHT, 1, true);
                
                if(event.key.keysym.scancode == SDL_SCANCODE_D && game.isMulti())
                    game.actionShip(GameEngin::RIGHT, 2, true);

                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    game.actionShip(GameEngin::FIRE, 1, true);
                
                if (event.key.keysym.scancode == SDL_SCANCODE_W && game.isMulti())
                    game.actionShip(GameEngin::FIRE, 2, true);
                break;

            case SDL_KEYUP:

                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                    game.actionShip(GameEngin::UP, 1, false);
                
                if(event.key.keysym.scancode == SDL_SCANCODE_Z && game.isMulti())
                    game.actionShip(GameEngin::UP, 2, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    game.actionShip(GameEngin::LEFT, 1, false);
                
                if(event.key.keysym.scancode == SDL_SCANCODE_Q && game.isMulti())
                    game.actionShip(GameEngin::LEFT, 2, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    game.actionShip(GameEngin::RIGHT, 1, false);

                if(event.key.keysym.scancode == SDL_SCANCODE_D && game.isMulti())
                    game.actionShip(GameEngin::RIGHT, 2, false);
                    
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    game.actionShip(GameEngin::FIRE, 1, false);
                
                if (event.key.keysym.scancode == SDL_SCANCODE_W && game.isMulti())
                    game.actionShip(GameEngin::FIRE, 2, false);

                if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    game.actionShip(GameEngin::ALIVE, 1, false);
                    if(game.isMulti())
                        game.actionShip(GameEngin::ALIVE, 2, false);
                }
                break;
            default:
                break;
        }
    }
}



void App::exec(int const& mod) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int prevFrame = 0;
    int nextFrame = SDL_GetTicks();
    srand(time(NULL));
    float dt = 0;
    float interpolation = 0;
    float rockTimer = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(5000, 50000);

    // float lifeTimer = 0;
    // float shootTimer = 0;

    if(mod == 1) {
        game.setMultiSimple(true);
        game.setPlayerPos(1);
    }

    if(mod == 2) {
        game.setMultiCombat(true);
        game.setPlayerPos(2);
    }

    while(isRunning) {

        if(SDL_GetTicks() > rockTimer + 4000) {
            game.spawnRock(Rock::BIGROCK);
            rockTimer = SDL_GetTicks();
        }
        // if(SDL_GetTicks() / 2000 > lifeTimer + 2*(dis(gen)) ) {
        //     game.spawnRock(Rock::LIFE);
        //     lifeTimer = SDL_GetTicks();
        // }
        // if(SDL_GetTicks() > shootTimer + dis(gen) + dis(gen)) {
        //     game.spawnRock(Rock::SHOOT);
        //     shootTimer = SDL_GetTicks();
        // }
        this->eventsHandler();
        dt = float(SDL_GetTicks() - prevFrame)/ 1000.0f;
        int count = 0;

        while (SDL_GetTicks() > nextFrame && count < 5) {
            game.updatePositions(dt);
            nextFrame += frameDelay;
            prevFrame = SDL_GetTicks();
            count++;
        }
        game.collisions();
        interpolation = float(SDL_GetTicks() + frameDelay - nextFrame) / float(frameDelay);
        game.interpolate(dt, interpolation);
        game.render(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

int main(int argc, char** argv){
    int opt;
    int multiS = 0;
    int multiC = 0;

    while((opt = getopt(argc,argv,"cm")) != -1) {
        switch (opt)
        {        
            case 'c':
                multiC = 1;
                break;
            case 'm':
                multiS = 1;
                break;
            case '?':
                fprintf(stderr, "Usage: ./Asteroid [-c|-m]\n-c for combat mod, -m for coop mod\n");
                exit(1);
        }
    }

    if(multiS && multiC) {
        fprintf(stderr, "Usage: ./Asteroid [-c|-m]\n-c for combat mod, -m for coop mod\n");
        exit(1);   
    }

    int mod = (multiS)? 1 : ((multiC)? 2 : 0);

    App app;
    app.exec(mod);
}