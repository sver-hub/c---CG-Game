#include "Enemy.h"
#include "Sprites.h"

class Enemy_Voodoo: public Enemy {

    public:
    Enemy_Voodoo(Field *_field, Point position = Point(0, 0)): Enemy(_field, position) {
        visionRadius = 8;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_voodoo;
    }
};