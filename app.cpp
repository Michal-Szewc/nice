#include "app.h"

// INITIALIZATION

void App::initVariables(){
    window = NULL;
    renderer = NULL;

    working = true;
    time=(double)SDL_GetTicks();
    deltaTime=0;

    snake = Snake(windowWidth,windowHeight,gridSize,speed);
    board = Map(&snake,appleNum,windowWidth,windowHeight,gridSize);

    state = GameState::GAME;
    paused = false;
    pHeld = false;
}

void App::initWindow(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth,windowHeight, 0, &(this->window), &(this->renderer));
    SDL_SetWindowTitle(window,"Snake Szewc Michal");
}

App::App(int width, int height, int _appleNum, int _gridSize, int _growth, double _speed, bool _fpsCap, double _speedMul):windowWidth(width),windowHeight(height),appleNum(_appleNum),
    gridSize(_gridSize),growth(_growth),speed(_speed),fpsCap(_fpsCap),speedMul(_speedMul){
    initVariables();
    initWindow();
}

// INPUT MANAGMENT

void App::handleInput(){
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        switch(e.type){
        case  SDL_QUIT:
            working = false;
            break;
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym){
            case SDLK_ESCAPE:
                working = false;
                break;
            case SDLK_p:
                if(!pHeld){
                    pHeld = true;
                    paused =!paused;
                }
                break;
            case SDLK_UP:
                snake.setDirection(Direction::UP);
                break;
            case SDLK_RIGHT:
                snake.setDirection(Direction::RIGHT);
                break;
            case SDLK_DOWN:
                snake.setDirection(Direction::DOWN);
                break;
            case SDLK_LEFT:
                snake.setDirection(Direction::LEFT);
                break;
            }
            break;
        default:
            pHeld = false;
            break;
        }
    }
}

// UPDATING APPLICATION

void App::update(){
    lastTime = time;
    time = (double)SDL_GetTicks();
    deltaTime = time - lastTime;

    if(!paused){
        snake.update(deltaTime);

        if(board.removeApple(snake.getPosition())){
            snake.grow(growth);
            snake.speedMul(speedMul);
            board.spawnApple();
        }

        if (snake.colides(GridPosition(snake.getPosition()))){
            state = GameState::GAMEOVER;
        }

        board.update(deltaTime);
    }
    SDL_Delay(fpsCap?std::max((int)(16 - deltaTime),0):0);
}

// RENDERING

void App::render(){
    SDL_SetRenderDrawColor(renderer,50,50,50,255);
    SDL_RenderClear(renderer);

    snake.render(renderer);
    board.render(renderer);

    SDL_RenderPresent(renderer);
}

// MAIN LOOP

void App::run(){

    // GAME LOOP

    while(this->working && state == GameState::GAME){
        handleInput();
        update();
        render();
    }
    if(this->working){

        // GAME OVER

        std::ofstream wyniki;
        wyniki.open("scores.txt",std::fstream::app);
        wyniki << "Length: " << snake.getLength() << " Map size: " << windowWidth/gridSize << " x " << windowHeight/gridSize << " Snake speed: " << speed << " Growth: " << growth
        << " Apple amount: " << appleNum << " fpsCap: " << fpsCap << " speed multiplier: " << speedMul << std::endl;
        wyniki.close();

        while(this->working && state == GameState::GAMEOVER){
            handleInput();
            render();
            SDL_Delay(30);
        }
    }
}
