#include "Player.h"
#include "config.h"
#include "Sprites.h"
#include "Field.h"

Player::Player(Field *_field, Point position) : Entity(_field, position) {
    Sprites *sprites = Sprites::GetInstance();
    textures = sprites->hero;
}

bool Player::move(MovementDir dir) {
    bool moved = false;

    if (field->isValid(pos + dirToVec(dir))) {
        makeMove(dir);
        moved = true;
    }
    setDirection(dir);
    return moved;
}