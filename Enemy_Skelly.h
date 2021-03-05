#include "Enemy.h"
#include "Sprites.h"

class Enemy_Skelly: public Enemy {

    public:
    Enemy_Skelly(Field *_field, Point position = Point(0, 0)): Enemy(_field, position) {
        visionRadius = 5;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_skelly;
        health = 5;
        maxHealth = health;
        attackDamage = 5;
        name = "Skelly";
    }
};