#ifndef PLAYER
#define PLAYER

#include "Entity.h"

class Player: public Entity {

    public:

    Player(Field *_field, Point position);

    bool move(MovementDir dir);

    ~Player() {}
};

#endif