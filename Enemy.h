#ifndef ENEMY
#define ENEMY

#include "Entity.h"
#include <vector>

class Field;

class Enemy: public Entity {

    protected:
    int visionRadius;


    bool seesPlayer(Point playerPos);

    bool hasEnemiesNearby(Point position);

    public:
    Enemy(Field *_field, Point position = Point(0, 0)) : Entity(_field, position) { }

    void move();

    bool spawn();
};

#endif