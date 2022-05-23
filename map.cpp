#include "map.h"

Map::Map(Snake* _snake, int _appleNum, int width, int height, int _gridSize):snake(_snake),appleNum(_appleNum),mapWidth(width),mapHeight(height),gridSize(_gridSize){
    for(int i=0; i < appleNum; ++i){
        spawnApple();
    }
}

void Map::update(double dt){
    while(apples.size() < std::min(appleNum,(mapWidth/gridSize) * (mapHeight/gridSize) - snake->getLength() - 1))
        spawnApple();
}

void Map::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    for(std::vector<SDL_Rect>::iterator it = apples.begin(); it != apples.end(); ++it) {
        SDL_RenderFillRect(renderer,&(*it));
    }
}

void Map::spawnApple(){
    if(apples.size() >= std::min(appleNum,(mapWidth/gridSize) * (mapHeight/gridSize) - snake->getLength() - 1))
        return;
    GridPosition pos;
    do{
        pos={rand()%(mapWidth/gridSize), rand()%(mapHeight/gridSize)};
    }while(getApple(pos) != nullptr || snake->colides(pos,false));
    apples.push_back(SDL_Rect{pos.x * gridSize,pos.y * gridSize,gridSize,gridSize});
}

SDL_Rect* Map::getApple(const GridPosition& position){
    int x = position.x * gridSize, y = position.y * gridSize;

    for(std::vector<SDL_Rect>::iterator it = apples.begin(); it != apples.end(); ++it) {
        if(it->x == x && it->y == y){
            return &(*it);
        }
    }
    return nullptr;
}

bool Map::removeApple(const GridPosition& position){
    int x = position.x * gridSize, y = position.y * gridSize;

    for(std::vector<SDL_Rect>::iterator it = apples.begin(); it != apples.end(); ++it) {
        if(it->x == x && it->y == y){
            apples.erase(it);
            return true;
        }
    }
    return false;
}
