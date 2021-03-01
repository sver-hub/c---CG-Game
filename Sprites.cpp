#include "Sprites.h"
      
Sprites* Sprites::singleton_= nullptr;;

Sprites *Sprites::GetInstance()
{
    if(singleton_==nullptr){
        singleton_ = new Sprites();
    }
    return singleton_;
}


void Sprites::load(Image &tiles) {
        
    wall_t.initTile(tiles, 16,496);
    wall.initTile(tiles, 16,480);
    wall_side_r.initTile(tiles, 0,368);
    wall_side_rb.initTile(tiles, 0,352);
    wall_side_l.initTile(tiles, 16,368);
    wall_side_lb.initTile(tiles, 16,352);
    wall_hole1.initTile(tiles, 48,464);
    wall_hole2.initTile(tiles, 48,448);
    wall_flag_red.initTile(tiles, 16,464);

    trap_1.initTile(tiles, 16,320);
    trap_2.initTile(tiles, 32,320);
    trap_3.initTile(tiles, 48,320);
    trap_4.initTile(tiles, 64,320);

    floor.initTile(tiles, 16, 432);
    floor_crack1.initTile(tiles, 32,432);
    floor_crack2.initTile(tiles, 48,432);
    floor_crack3.initTile(tiles, 32,416);
    floor_crack4.initTile(tiles, 48,416);
    floor_crack_left.initTile(tiles, 16,400);
    floor_crack_right.initTile(tiles, 32,400);

    hero_t.initTile(tiles, 144,400);
    hero.initTile(tiles, 144,384);
    }