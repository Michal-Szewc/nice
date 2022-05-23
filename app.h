#ifndef APP_H
#define APP_H

#include "map.h"

enum GameState{
    MENU,
    GAME,
    GAMEOVER
};

class App{
private:
    int windowWidth;
    int windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;

    int gridSize;

    bool working;
    double time;
    double lastTime;
    double deltaTime;

    Snake snake;
    int growth;
    double speed;
    double speedMul;

    Map board;
    int appleNum;

    bool paused;
    bool pHeld;
    bool fpsCap;
    GameState state;

    void initVariables();
    void initWindow();

    void handleInput();
    void update();

    void render();

public:
    App(int width, int height,int _appleNum, int _gridSize, int _growth, double speed, bool fpsCap, double speedMul);
    void run();
};

#endif // APP_H
