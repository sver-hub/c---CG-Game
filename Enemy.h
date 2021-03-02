#ifndef ENEMY
#define ENEMY

#include "Entity.h"
#include <vector>
class Field;

class Enemy: public Entity {

    protected:
    int visionRadius;

    Field *field;

    bool seesPlayer(Point playerPos);

    bool hasEnemiesNearby(std::vector<Enemy*> enemies);

    public:
    Enemy(Field *_field, Point position = Point{.x = 0, .y = 0}) : Entity(position) {
        field = _field;
    }

    void move(char *grid, Point playerPos);

    bool spawn(char *grid, Point playerPos, std::vector<Enemy*> enemies);
};

#endif