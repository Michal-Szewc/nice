#ifndef MAP_H
#define MAP_H

#include "snake.h"

class Map{
private:
    int mapWidth;
    int mapHeight;
    int appleNum;
    int gridSize;

    std::vector<SDL_Rect> apples;

    Snake* snake;
public:
    Map(){};
    Map(Snake* _snake, int width, int height, int _appleNum, int _gridSize = 10);
    void update(double dt);
    void render(SDL_Renderer* renderer);

    void spawnApple();
    SDL_Rect* getApple(const GridPosition& position);
    bool removeApple(const GridPosition& position);
};

#endif // MAP_H
