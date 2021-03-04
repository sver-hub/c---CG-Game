#include "Entity.h"
#include "config.h"


void Entity::draw(Image &screen, CameraController camera) {
    if (!camera.isSpriteVisible(getSpritePos())) return;

    Image *toDraw;
    Image *toDraw_t;
    if (animationState > 0) {
        animationState -=2;
        idleState = 0;
    }
    bool left = looksLeft();
    
    if (idleState < fps/4) {
        toDraw = left ? &textures->bottom_l : &textures->bottom_r;
        toDraw_t = left ? &textures->top_l : &textures->top_r;
    }
    else if (idleState < 2 * fps/4) {
        toDraw = left ? &textures->bottom_l_idle_1 : &textures->bottom_r_idle_1;
        toDraw_t = left ? &textures->top_l_idle_1 : &textures->top_r_idle_1;
    }
    else if (idleState < 3 * fps/4) {
        toDraw = left ? &textures->bottom_l_idle_2 : &textures->bottom_r_idle_2;
        toDraw_t = left ? &textures->top_l_idle_2 : &textures->top_r_idle_2;
    }
    else if (idleState < 4 * fps/4) {
        toDraw = left ? &textures->bottom_l_idle_3 : &textures->bottom_r_idle_3;
        toDraw_t = left ? &textures->top_l_idle_3 : &textures->top_r_idle_3;
    }
    
    idleState = (idleState + 1)%fps;

    screen.putSprite(getSpritePos().x, getSpritePos().y, *toDraw, camera);
    screen.putSprite(getSpritePos().x, getSpritePos().y + TILE_SIZE, *toDraw_t, camera);
}

Point Entity::getSpritePos() {
    if (animationState == 0) return Point(pos.x * TILE_SIZE, GRID_SIZE*TILE_SIZE - pos.y * TILE_SIZE);
    else {
        return Point(pos.x * TILE_SIZE, GRID_SIZE*TILE_SIZE - pos.y * TILE_SIZE) - 
            Point (animationState * dirToVec(direction).x, -animationState * dirToVec(direction).y);
    }
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