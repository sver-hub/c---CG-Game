#include "Entity.h"
#include "config.h"
#include "Field.h"
#include <iostream>


void Entity::draw(Image &screen, CameraController camera) {
    if (!camera.isSpriteVisible(getSpritePos())) return;

    Image *toDraw;
    Image *toDraw_t;
    if (animationState > 0) {
        animationState -=2;
        idleState = 0;
    }

    if (deathState > 0) {
        int d = 3 - 4 * deathState /fps;
        toDraw = textures->death[d];
        screen.putSprite(getSpritePos().x, getSpritePos().y + 5, *toDraw, camera);
        deathState = std::max(deathState - 1, 1);
        return;
    }
    
    bool left = looksLeft();
    int k = 3 - 4 * idleState / fps;
    toDraw = left ? textures->bottom_left[k] : textures->bottom_right[k];
    toDraw_t = left ? textures->top_left[k] : textures->top_right[k];
    
    idleState = (idleState + 1)%fps;

    if (damagedState <= 0) {
        screen.putSprite(getSpritePos().x, getSpritePos().y, *toDraw, camera);
        screen.putSprite(getSpritePos().x, getSpritePos().y + TILE_SIZE, *toDraw_t, camera);
    } else {
        screen.putSprite(getSpritePos().x, getSpritePos().y, *toDraw, camera, red);
        screen.putSprite(getSpritePos().x, getSpritePos().y + TILE_SIZE, *toDraw_t, camera, red);
        damagedState--;
        if (damagedState == 0 && !isAlive()) {
            deathState = fps/2;
        }
    }

    displayHealth(screen, camera);

}

void Entity::drawAttack(Image &screen, CameraController camera) {
    if (attackState <= 0) return;

    attackState -= 4;
    idleState = 0;
    int x_shift = 0;
    int y_shift = 0;
    Image *attackSprite;
    int a = 3 - 4 * attackState / fps;
    if (direction == MovementDir::RIGHT) {
        attackSprite = textures->attack_right[a];
        x_shift += TILE_SIZE/2;
    } else if (direction == MovementDir::LEFT) {
        attackSprite = textures->attack_left[a];
        x_shift -= TILE_SIZE/2;
    } else if (direction == MovementDir::UP) {
        attackSprite = textures->attack_up[a];
        y_shift += TILE_SIZE;
    } else if (direction == MovementDir::DOWN) {
        attackSprite = textures->attack_down[a];
        y_shift -= TILE_SIZE/2;
    }
    screen.putSprite(getSpritePos().x + x_shift, getSpritePos().y + y_shift, *attackSprite, camera);
    
}

void Entity::displayHealth(Image& screen, CameraController camera) {
    Point p = getSpritePos();
    float healthEnd = health*(TILE_SIZE-4)/maxHealth;
    for (int j = 0; j < 2; j++) {
        for (int i = 2; i < TILE_SIZE-4; i++) {
            int w = p.x - camera.x0 + i + (SCREEN_WIDTH-2*camera.radius)/2;
            int h = p.y - camera.y0 + j + (SCREEN_HEIGHT-2*camera.radius)/2 - TILE_SIZE;
            if (w < 0 || w > SCREEN_WIDTH || h < 0 || h > SCREEN_HEIGHT) continue;
            screen.putPixel(w, h + 3*TILE_SIZE/2, i - 2 < healthEnd ? red : black);
        }
    }
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

bool Entity::attack(Point p) {
    Entity* e = field->getEntityAtPos(p);
    if (!e->isAlive()) return false;
    
    e->takeDamage(attackDamage);
    attackState = fps;
    return true;
}

void Entity::takeDamage(int damage) {
    health = std::max(health - damage, 0);
    damagedState = fps/4; 
    std::cout << name << " took " << damage << " damage. " << health << " remaininig" << std::endl;
}