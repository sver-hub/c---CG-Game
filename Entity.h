#ifndef ENTITY
#define ENTITY

#include "Image.h"
#include "config.h"
#include "TextureSet.h"

struct Point {
    int x;
    int y;
};

enum class MovementDir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Entity {

    protected:
    TextureSet *textures;

    static Point dirToVec(MovementDir dir);

    void makeMove(MovementDir dir);

    void setDirection(MovementDir dir);

    void drawIdle(Image &screen);

    Point pos;
    Point prev_pos;
    MovementDir direction = MovementDir::LEFT;
    MovementDir turnDir = MovementDir::LEFT;
    int animationState = 0;
    int idleState = 0;

    void updatePrevPos() { prev_pos.x = pos.x; prev_pos.y = pos.y; }

    public:

    Entity(Point position): pos(position), prev_pos(position) {}

    ~Entity() {}

    Point getPos() { return pos; }

    Point getPrevPos() { return prev_pos; }

    bool looksLeft() { return turnDir == MovementDir::LEFT; }

    void draw(Image &screen);    
};

#endif