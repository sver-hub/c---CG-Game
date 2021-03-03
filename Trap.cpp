#include "Trap.h"

Trap::Trap(Point position): pos(position) {
        Sprites *sprites = Sprites::GetInstance();
        textures.push_back(&sprites->trap_2);
        textures.push_back(&sprites->trap_4);
}

void Trap::draw(Image &screen) {
        screen.putTile(pos.x, pos.y, *textures[activated == 0 ? 0 : 1]);
}

bool Trap::check(Point p, int num_ent) {
    if (pos == p) {

        activated = num_ent;
        return true;
    }
    activated = activated - 1 > 0 ? activated - 1 : 0;
    return false;
}