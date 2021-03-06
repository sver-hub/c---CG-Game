#include "Player.h"
#include "config.h"
#include "Sprites.h"
#include "Field.h"
#include <iostream>

Player::Player(Field* _field, Point position) : Entity(_field, position) {
    Sprites *sprites = Sprites::GetInstance();
    textures = sprites->hero;
    health = 30;
    maxHealth = health;
    attackDamage = 15;
    name = "Player";
}

bool Player::move(MovementDir dir) {
    bool moved = false;
   
   Point p = pos + dirToVec(dir);
    if (field->isValid(p)) {
        makeMove(dir);
        moved = true;
        if (field->isTrap(p)) takeDamage(15);
    } else if (field->isEnemy(p)) {
        if (attack(p)) moved = true;
    }
    setDirection(dir);
    return moved;
}
