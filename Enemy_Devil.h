#include "Enemy.h"
#include "Sprites.h"

class Enemy_Devil: public Enemy {

    public:
    Enemy_Devil(Field *_field, Point position = Point(0, 0)): Enemy(_field, position) {
        visionRadius = 10;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_devil;
    }
};