#include "Enemy.h"
#include "Sprites.h"

class Enemy_Cultist: public Enemy {

    public:
    Enemy_Cultist(Field *_field, Point position = Point(0, 0)): Enemy(_field, position) {
        visionRadius = 7;
        Sprites *sprites = Sprites::GetInstance();
        textures = sprites->enemy_cultist;
        health = 15;
        maxHealth = health;
        attackDamage = 10;
        name = "Cultist";
    }
};