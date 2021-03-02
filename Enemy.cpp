#include "Enemy.h"
#include "Field.h"

bool Enemy::seesPlayer(Point playerPos) {
    return ((abs(playerPos.x - pos.x) <= visionRadius) && (abs(playerPos.y - pos.y) <= visionRadius));
}

void Enemy::move(char *grid, Point playerPos) {
    if (seesPlayer(playerPos)) {

    } else {
        MovementDir dir;
        int k = rand()%7;
        if (k < 1) {        //go up
            dir = MovementDir::UP;
        }
        else if (k < 2) {   //go right
            dir = MovementDir::RIGHT;
        }
        else if (k < 3) {   //go down
            dir = MovementDir::DOWN;
        }
        else if (k < 4) {   //go left
            dir = MovementDir::LEFT;
        }
        else {              //idle
            return;
        }
        Point dirVec = dirToVec(dir);
        Point goTo = Point{.x = pos.x + dirVec.x, .y = pos.y + dirVec.y};
        if (field->isValid(goTo))
            makeMove(dir);
        setDirection(dir);
    }
}

bool Enemy::spawn(char *grid, Point playerPos, std::vector<Enemy*> enemies) {
    
    for (int i = 0; i < 1000; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        if (grid[y * GRID_SIZE + x] != cfloor || seesPlayer(playerPos) || hasEnemiesNearby(enemies)) 
            continue;
        
        pos.x = x;
        pos.y = y;
        updatePrevPos();
        return true;
    }

    return false;
}

bool Enemy::hasEnemiesNearby (std::vector<Enemy*> enemies) {
    for (const auto &enemy : enemies) {
        if (abs(pos.x - enemy->pos.x) + abs(pos.y - enemy->pos.y) == 1) 
            return true;
    }
    return false;
}