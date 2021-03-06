#include "Trap.h"
#include "Field.h"

Trap::Trap(Point position): pos(position) {
        Sprites *sprites = Sprites::GetInstance();
        textures.push_back(&sprites->trap_2);
        textures.push_back(&sprites->trap_4);
}

void Trap::draw(Image &screen, CameraController camera) {
    if (!camera.isSpriteVisible(Point(pos.x * TILE_SIZE, GRID_SIZE*TILE_SIZE - pos.y * TILE_SIZE))) return;
    screen.putSprite(pos.x * TILE_SIZE, GRID_SIZE*TILE_SIZE - pos.y * TILE_SIZE, *textures[activated == 0 ? 0 : 1], camera);
}

bool Trap::check(Point p, int num_ent) {
    if (pos == p) {
        activated = num_ent;
        return true;
    }
    activated = activated - 1 > 0 ? activated - 1 : 0;
    return false;
}