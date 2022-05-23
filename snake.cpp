#include "snake.h"

Snake::Snake(int x, int y,int _gridSize, double _speed):gridPosition(x/_gridSize/2,y/_gridSize/2),direction(Direction::RIGHT),
    moving(Direction::RIGHT),speed(_speed * 0.01 * (double)_gridSize),length(1),gridSize(_gridSize),mapWidth(x/_gridSize),mapHeight(y/_gridSize){
    head = {x/2,y/2,gridSize,gridSize};
}

void Snake::render(SDL_Renderer* renderer){
    SDL_Rect horizontal{0,0,gridSize - 2 * (gridSize/SEGMENT_FRACTION),2 * (gridSize/SEGMENT_FRACTION)};
    SDL_Rect vertical{0,0,2 * (gridSize/SEGMENT_FRACTION),gridSize - 2 * (gridSize/SEGMENT_FRACTION)};
    SDL_Rect* prev = nullptr;

    for(std::deque<SDL_Rect>::iterator it = body.begin(); it != body.end(); ++it) {
        SDL_SetRenderDrawColor(renderer,48, 207, 103,255);
        SDL_RenderFillRect(renderer,&(*it));
        if(prev){
            SDL_SetRenderDrawColor(renderer,41, 163, 83,255);

            // SEGMENT OBOK

            if(prev->x - it-> x == gridSize){
                vertical.x = it->x + gridSize - 2 * (gridSize/SEGMENT_FRACTION);
                vertical.y = it->y;
                SDL_RenderFillRect(renderer,&vertical);
            }
            else if(prev->x - it->x == -gridSize){
                vertical.x = it->x - 2 * (gridSize/SEGMENT_FRACTION);
                vertical.y = it->y;
                SDL_RenderFillRect(renderer,&vertical);
            }
            else if(prev->y - it-> y == gridSize){
                horizontal.y = it->y + gridSize - 2 * (gridSize/SEGMENT_FRACTION);
                horizontal.x = it->x;
                SDL_RenderFillRect(renderer,&horizontal);
            }
            else if(prev->y - it-> y == -gridSize){
                horizontal.y = it->y - 2 * (gridSize/SEGMENT_FRACTION);
                horizontal.x = it->x;
                SDL_RenderFillRect(renderer,&horizontal);
            }

            // SEGMENT PO TELEPORTACJI

            else if (prev->x < it->x){
                vertical.x = it->x + gridSize - 2 * (gridSize/SEGMENT_FRACTION);
                vertical.y = it->y;
                SDL_RenderFillRect(renderer,&vertical);
                vertical.x = prev->x - 2 * (gridSize/SEGMENT_FRACTION);
                vertical.y = it->y;
                SDL_RenderFillRect(renderer,&vertical);
            }
            else if(prev->x > it->x){
                vertical.x = it->x - 2 * (gridSize/SEGMENT_FRACTION);
                vertical.y = it->y;
                SDL_RenderFillRect(renderer,&vertical);
                vertical.x = prev->x + gridSize - 2 * (gridSize/SEGMENT_FRACTION);
                vertical.y = it->y;
                SDL_RenderFillRect(renderer,&vertical);
            }
            else if(prev->y < it->y){
                horizontal.y = it->y + gridSize - 2 * (gridSize/SEGMENT_FRACTION);
                horizontal.x = it->x;
                SDL_RenderFillRect(renderer,&horizontal);
                horizontal.y = prev->y - 2 * (gridSize/SEGMENT_FRACTION);
                horizontal.x = it->x;
                SDL_RenderFillRect(renderer,&horizontal);
            }
            else if(prev->y > it->y){
                horizontal.y = it->y - 2 * (gridSize/SEGMENT_FRACTION);
                horizontal.x = it->x;
                SDL_RenderFillRect(renderer,&horizontal);
                horizontal.y = prev->y + gridSize - 2 * (gridSize/SEGMENT_FRACTION);
                horizontal.x = it->x;
                SDL_RenderFillRect(renderer,&horizontal);
            }
        }
        prev = &(*it);
    }

    SDL_SetRenderDrawColor(renderer,65, 176, 146,255);
    SDL_RenderFillRect(renderer,&head);
}

void Snake::update(double dt){
    changePosition(dt);

    if(head.x/gridSize != gridPosition.x || head.y/gridSize != gridPosition.y){
        body.push_front(SDL_Rect{head.x/gridSize*gridSize + gridSize/SEGMENT_FRACTION,head.y/gridSize*gridSize + gridSize/SEGMENT_FRACTION,
                                gridSize - 2 * (gridSize/SEGMENT_FRACTION),gridSize - 2 * (gridSize/SEGMENT_FRACTION)});
        while(body.size() > length - 1)
            body.pop_back();

        head.x = gridPosition.x * gridSize;
        head.y = gridPosition.y * gridSize;
    }
}

void Snake::setDirection(const Direction& _direction){
    switch(moving){
    case UP:
        direction = (_direction == Direction::DOWN)?direction:_direction;
        break;
    case RIGHT:
        direction = (_direction == Direction::LEFT)?direction:_direction;
        break;
    case DOWN:
        direction = (_direction == Direction::UP)?direction:_direction;
        break;
    case LEFT:
        direction = (_direction == Direction::RIGHT)?direction:_direction;
        break;
    }
}

void Snake::changePosition(double dt){
    movement += dt * speed;
    if(movement > gridSize){
        moving = direction;
        switch(moving){
        case UP:
            --gridPosition.y;
            break;
        case RIGHT:
            ++gridPosition.x;
            break;
        case DOWN:
            ++gridPosition.y;
            break;
        case LEFT:
            --gridPosition.x;
            break;
        }

        // TELEPORTUJ SIE JEZELI POZA MAPA

        if(gridPosition.x == mapWidth)
            gridPosition.x = 0;
        else if(gridPosition.x == -1)
            gridPosition.x = mapWidth - 1;
        else if(gridPosition.y == mapHeight)
            gridPosition.y = 0;
        else if(gridPosition.y == -1)
            gridPosition.y = mapHeight - 1;
        movement -= gridSize;
    }
}

bool Snake::colides(const GridPosition& position, bool avoidHead){
    int x = position.x * gridSize + gridSize/SEGMENT_FRACTION, y = position.y * gridSize + gridSize/SEGMENT_FRACTION;

    for(std::deque<SDL_Rect>::iterator it = body.begin(); it != body.end(); ++it) {
        if(it->x == x && it->y == y && (!avoidHead || (avoidHead && it != body.begin()))){
            return true;
        }
    }
    return false;
}

