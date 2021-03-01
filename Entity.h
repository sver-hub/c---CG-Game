#include "Image.h"
#include "config.h"

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
    
    Image texture_r;
    Image texture_r_t;
    Image texture_l = Image(TILE_SIZE, TILE_SIZE, 4);
    Image texture_l_t = Image(TILE_SIZE, TILE_SIZE, 4);

    protected:

    Point pos;
    Point prev_pos;
    MovementDir direction = MovementDir::LEFT;
    MovementDir turnDir = MovementDir::LEFT;
    int animationState = 0;

    void updatePrevPos() { prev_pos.x = pos.x; prev_pos.y = pos.y; }

    public:

    Entity(Point position): pos(position), prev_pos(position) {}

    ~Entity() {}

    void setTextures(Image &texture_bottom, Image &texture_top);

    Point getPos() { return pos; }

    Point getPrevPos() { return prev_pos; }

    Point dirToVec();

    bool moved() { return !(pos.x == prev_pos.x && pos.y == prev_pos.y); }

    bool looksLeft() { return turnDir == MovementDir::LEFT; }

    void draw(Image &screen);    
};