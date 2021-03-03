#include "Entity.h"
#include "config.h"


void Entity::draw(Image &screen) {
    int shift_x = 0;
    int shift_y = 0;
    int shift_x_prev = 0;
    int shift_y_prev = 0;
    Image *toDraw;
    Image *toDraw_t;
    if (animationState > 0) {
        shift_x += animationState * dirToVec(direction).x;
        shift_y -= animationState * dirToVec(direction).y;
        shift_x_prev -= (TILE_SIZE - animationState) * dirToVec(direction).x;
        shift_y_prev += (TILE_SIZE - animationState) * dirToVec(direction).y;

        animationState -=2;
        idleState = 0;
    }
    if (looksLeft()) {
        if (idleState < fps/4) {
            toDraw = &textures->bottom_l;
            toDraw_t = &textures->top_l;
        }
        else if (idleState < 2 * fps/4) {
            toDraw = &textures->bottom_l_idle_1;
            toDraw_t = &textures->top_l_idle_1;
        }
        else if (idleState < 3 * fps/4) {
            toDraw = &textures->bottom_l_idle_2;
            toDraw_t = &textures->top_l_idle_2;
        }
        else if (idleState < 4 * fps/4) {
            toDraw = &textures->bottom_l_idle_3;
            toDraw_t = &textures->top_l_idle_3;
        }
    }
    else {
        if  (idleState < fps/4) {
            toDraw = &textures->bottom_r;
            toDraw_t = &textures->top_r;
        }
        else if (idleState < 2 * fps/4) {
            toDraw = &textures->bottom_r_idle_1;
            toDraw_t = &textures->top_r_idle_1;
        }
        else if (idleState < 3 * fps/4) {
            toDraw = &textures->bottom_r_idle_2;
            toDraw_t = &textures->top_r_idle_2;
        }
        else if (idleState < 4 * fps/4) {
            toDraw = &textures->bottom_r_idle_3;
            toDraw_t = &textures->top_r_idle_3;
        }
    }
    idleState = (idleState + 1)%fps;
    
    if (shift_x_prev != 0 || shift_y_prev != 0) {
        screen.putTile(prev_pos.x, prev_pos.y, *toDraw, 0, 0, shift_x_prev,  shift_y_prev);
        screen.putTile(prev_pos.x, prev_pos.y-1, *toDraw_t, 0, 0, shift_x_prev, shift_y_prev);
    }
    screen.putTile(pos.x, pos.y, *toDraw, 0, 0, shift_x, shift_y);
    screen.putTile(pos.x, pos.y-1, *toDraw_t, 0, 0, shift_x, shift_y);
}

void Entity::drawIdle(Image &screen) {

}

void Entity::makeMove(MovementDir dir) {
    updatePrevPos();
    animationState = TILE_SIZE - 2;
    pos += dirToVec(dir);
}

void Entity::setDirection(MovementDir dir) {
    direction = dir;
    if (dir == MovementDir::LEFT || dir == MovementDir::RIGHT) {
        turnDir = dir;
    }
}