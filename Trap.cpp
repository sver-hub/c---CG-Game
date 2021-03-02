#include "Trap.h"

Trap::Trap(Point position): pos(position) {
        Sprites *sprites = Sprites::GetInstance();
        textures.push_back(&sprites->trap_2);
        textures.push_back(&sprites->trap_3);
        textures.push_back(&sprites->trap_4);
}

void Trap::draw(Image &screen) {
    screen.putTile(pos.x, pos.y, *textures[0]);
}