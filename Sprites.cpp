#include "Sprites.h"
      
Sprites* Sprites::singleton_= nullptr;;

Sprites *Sprites::GetInstance() {
    if (singleton_== nullptr){
        singleton_ = new Sprites();
    }
    return singleton_;
}


void Sprites::load(Image &tiles, Image &words, Image &_fire) {
        
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

    fire.initTile(_fire, 0, 0);

    exit.initTile(tiles, 48,400);

    int y_shift = 5;

    hero = new TextureSet(tiles, 144, 384 - y_shift);
    enemy_slime = new TextureSet(tiles, 432, 384 - y_shift);
    enemy_skelly = new TextureSet(tiles, 368, 416 - y_shift);
    enemy_goblin = new TextureSet(tiles, 368, 288 - y_shift);
    enemy_voodoo = new TextureSet(tiles, 368, 320 - y_shift);
    enemy_cultist = new TextureSet(tiles, 368, 224 - y_shift);
    enemy_devil = new TextureSet(tiles, 368, 160 - y_shift);
    enemy_angel = new TextureSet(tiles, 368, 128 - y_shift);
    
    victory.initWord(words, 16, 624, 144, 28);
    level1.initWord(words, 16, 480, 128, 28);
    level2.initWord(words, 16, 320, 128, 28);
    level3.initWord(words, 16, 160, 128, 28);
    game_over.initWord(words, 0, 0, 180, 28);
}