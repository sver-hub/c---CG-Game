#include "Entity.h"
#include "config.h"

void Entity::setTextures(Image &texture_bottom, Image &texture_top) {
    texture_r = texture_bottom;
    texture_r_t = texture_top;
    texture_l.mirror(texture_r);
    texture_l_t.mirror(texture_r_t);
}

void Entity::draw(Image &screen) {
    int shift_x = 0;
    int shift_y = 0;
    int shift_x_prev = 0;
    int shift_y_prev = 0;
    if (animationState > 0) {
        shift_x += animationState * dirToVec().x;
        shift_y -= animationState * dirToVec().y;
        shift_x_prev -= (TILE_SIZE - animationState) * dirToVec().x;
        shift_y_prev += (TILE_SIZE - animationState) * dirToVec().y;
    }
    if (looksLeft()) {
        if (shift_x_prev != 0 || shift_y_prev != 0) {
            screen.putTile(prev_pos.x, prev_pos.y, texture_l, 0, 0, shift_x_prev,  shift_y_prev);
            screen.putTile(prev_pos.x, prev_pos.y-1, texture_l_t, 0, 0, shift_x_prev, shift_y_prev);
        }
        screen.putTile(pos.x, pos.y, texture_l, 0, 0, shift_x, shift_y);
        screen.putTile(pos.x, pos.y-1, texture_l_t, 0, 0, shift_x, shift_y);
    } else {
        if (shift_x_prev != 0 || shift_y_prev != 0) {
            screen.putTile(prev_pos.x, prev_pos.y, texture_r, 0, 0, shift_x_prev,  shift_y_prev);
            screen.putTile(prev_pos.x, prev_pos.y-1, texture_r_t, 0, 0, shift_x_prev, shift_y_prev);
        }
        screen.putTile(pos.x, pos.y, texture_r, 0, 0, shift_x, shift_y);
        screen.putTile(pos.x, pos.y-1, texture_r_t, 0, 0, shift_x, shift_y);
    }

    if (animationState > 0) animationState -=2;
}

Point Entity::dirToVec() {
    switch (direction)
    {
    case MovementDir::LEFT:
        return Point{.x = -1, .y = 0};

    case MovementDir::RIGHT:
        return Point{.x = 1, .y = 0};
    
    case MovementDir::UP:
        return Point{.x = 0, .y = -1};

    case MovementDir::DOWN:
        return Point{.x = 0, .y = 1};
    
    default:
        break;
    }
}