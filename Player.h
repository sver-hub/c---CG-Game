#ifndef PLAYER
#define PLAYER

#include "Entity.h"

class Player: public Entity {

    public:

    Player(Point position);

    bool move(MovementDir dir, char *grid);
};

#endif