#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include <algorithm>
#include <deque>
#include <fstream>

#include "SDL2/SDL.h"

#define SEGMENT_FRACTION 5

struct GridPosition{
    int x;
    int y;

    GridPosition(){}
    GridPosition(const int& _x, const int& _y):x(_x),y(_y){}

    bool operator==(const GridPosition& other){return this->x == other.x && this->y == other.y;}
    bool operator!=(const GridPosition& other){return !(*this == other);}
};

enum Direction{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

#endif // DEFINES_H
