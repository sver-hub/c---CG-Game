#include "Enemy.h"
#include "Sprites.h"

class Enemy_Angel: public Enemy {

    public:
    Enemy_Angel(Field *_field, Point position = Point(0, 0)): Enemy(_field, position) {
        visionRadius = 12;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_angel;
    }
};