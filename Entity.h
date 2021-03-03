#ifndef ENTITY
#define ENTITY

#include "Image.h"
#include "config.h"
#include "TextureSet.h"
#include "Structures.h"

class Field;

class Entity {

    protected:

    void makeMove(MovementDir dir);

    void setDirection(MovementDir dir);

    void drawIdle(Image &screen);

    Point pos;
    Point prev_pos;
    MovementDir direction = MovementDir::LEFT;
    MovementDir turnDir = MovementDir::LEFT;
    TextureSet *textures;
    Field* field;
    int animationState = 0;
    int idleState = 0;

    void updatePrevPos() { prev_pos.x = pos.x; prev_pos.y = pos.y; }

    public:

    Entity(Field* _field, Point position): pos(position), prev_pos(position), field(_field) {}

    ~Entity() {}

    Point getPos() { return pos; }

    void setPos(Point p) { pos = p; }

    Point getPrevPos() { return prev_pos; }

    bool looksLeft() { return turnDir == MovementDir::LEFT; }

    void draw(Image &screen); 
};

#endif