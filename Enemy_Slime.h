#include "Enemy.h"

class Enemy_Slime: public Enemy {

    public:
    Enemy_Slime(Field *_field, Point position = Point{.x = 0, .y = 0}): Enemy(_field, position) {
        visionRadius = 5;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_slime;
    }
};