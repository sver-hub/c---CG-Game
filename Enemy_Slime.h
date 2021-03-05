#include "Enemy.h"
#include "Sprites.h"

class Enemy_Slime: public Enemy {

    public:
    Enemy_Slime(Field *_field, Point position = Point(0, 0)): Enemy(_field, position) {
        visionRadius = 5;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_slime;
        health = 30;
        maxHealth = health;
        attackDamage = 5;
        name = "Slime";
    }
};