#ifndef SNAKE_H
#define SNAKE_H

#include "defines.h"

class Snake{
private:
    GridPosition gridPosition;
    Direction direction;
    Direction moving;
    double speed;
    double movement;
    int length;
    int gridSize;
    int mapWidth;
    int mapHeight;

    SDL_Rect head;
    std::deque<SDL_Rect> body;
public:
    Snake(){}
    Snake(int x,int y,int _gridSize, double _speed);
    void update(double dt);
    void render(SDL_Renderer* renderer);

    void setDirection(const Direction& _direction);
    void changePosition(double dt);

    GridPosition getPosition()const{return gridPosition;}

    bool colides(const GridPosition& position, bool avoidHead = true);
    void grow(int amount){length += amount;}

    int getLength()const{return body.size();}

    void speedMul(double x){speed = speed * x;}
};

#endif //SNAKE_H
