#include "Player.h"
#include "config.h"
#include "Sprites.h"
#include "Field.h"
#include <iostream>

Player::Player(Field* _field, Point position) : Entity(_field, position) {
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

// void Player::draw(Image &screen, CameraController camera) {
//     Image *toDraw;
//     Image *toDraw_t;
//     if (animationState > 0) {
//         animationState -=2;
//         idleState = 0;
//     }
//     bool left = looksLeft();
    
//     if (idleState < fps/4) {
//         toDraw = left ? &textures->bottom_l : &textures->bottom_r;
//         toDraw_t = left ? &textures->top_l : &textures->top_r;
//     }
//     else if (idleState < 2 * fps/4) {
//         toDraw = left ? &textures->bottom_l_idle_1 : &textures->bottom_r_idle_1;
//         toDraw_t = left ? &textures->top_l_idle_1 : &textures->top_r_idle_1;
//     }
//     else if (idleState < 3 * fps/4) {
//         toDraw = left ? &textures->bottom_l_idle_2 : &textures->bottom_r_idle_2;
//         toDraw_t = left ? &textures->top_l_idle_2 : &textures->top_r_idle_2;
//     }
//     else if (idleState < 4 * fps/4) {
//         toDraw = left ? &textures->bottom_l_idle_3 : &textures->bottom_r_idle_3;
//         toDraw_t = left ? &textures->top_l_idle_3 : &textures->top_r_idle_3;
//     }
    
//     idleState = (idleState + 1)%fps;

//     screen.putTile(pos.x, pos.y, *toDraw);
//     screen.putTile(pos.x, pos.y-1, *toDraw_t);
// }