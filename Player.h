#include "Entity.h"

class Player: public Entity {

    public:

    Player(Point position) : Entity(position) {}

    void move(MovementDir dir, char *grid);
};