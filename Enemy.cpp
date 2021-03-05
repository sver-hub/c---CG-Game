#include "Enemy.h"
#include "Field.h"

bool Enemy::seesPlayer(Point playerPos) {
    return ((abs(playerPos.x - pos.x) <= visionRadius) && (abs(playerPos.y - pos.y) <= visionRadius));
}

void Enemy::move() {
    Point playerPos = field->getPlayer()->getPos();

    if (seesPlayer(playerPos)) {
        MovementDir randDir = randomDir();
        for (int i = 0; i < 4; i++) {
            MovementDir dir = randDir;
            dir = static_cast<MovementDir>((static_cast<int>(dir) + i)%4);
            Point p = pos + dirToVec(dir);

            if (field->isValid(p))
            {
                if (p.dist(playerPos) < pos.dist(playerPos)) {
                    makeMove(dir);
                    setDirection(dir);
                    return;
                }
            } else if (field->isPlayer(p)) {
                setDirection(dir);
                attack(p);
                return;
            }

        }
        return;
    } else {
        MovementDir dir;
        int k = rand()%2;
        if (k == 0)  return;

        dir = randomDir();
        Point goTo = pos + dirToVec(dir);
        if (field->isValid(goTo))
            makeMove(dir);
        setDirection(dir);
    }
}

bool Enemy::spawn() {
    Point playerPos = field->getPlayer()->getPos();
    
    for (int i = 0; i < 1000; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        if (field->getGrid()[y * GRID_SIZE + x] != cfloor  || hasEnemiesNearby(Point(x,y))) 
            continue;
        
        pos.x = x;
        pos.y = y;
        updatePrevPos();
        return true;
    }

    return false;
}

bool Enemy::hasEnemiesNearby (Point position) {
    for (const auto &enemy : field->getEnemies()) {
        if (position.dist(enemy->pos) == 1) 
            return true;
    }
    return false;
}