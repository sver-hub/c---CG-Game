#ifndef SPRITES
#define SPRITES

#include <string>
#include "Image.h"
#include "config.h"
#include "TextureSet.h"

class Sprites
{

protected:
    Sprites(){}

    static Sprites* singleton_;

public:

    Sprites(Sprites &other) = delete;
    
    void operator=(const Sprites &) = delete;
   
    static Sprites *GetInstance();

    void load(Image &tiles, Image &words);

    Image wall_t = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_side_r = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_side_rb = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_side_l = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_side_lb = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_hole1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_hole2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image wall_flag_red = Image(TILE_SIZE, TILE_SIZE, 4);

    Image trap_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image trap_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image trap_3 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image trap_4 = Image(TILE_SIZE, TILE_SIZE, 4);

    Image floor = Image(TILE_SIZE, TILE_SIZE, 4);
    Image floor_crack1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image floor_crack2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image floor_crack3 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image floor_crack4 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image floor_crack_left = Image(TILE_SIZE, TILE_SIZE, 4);
    Image floor_crack_right = Image(TILE_SIZE, TILE_SIZE, 4);

    Image exit = Image(TILE_SIZE, TILE_SIZE, 4);

    Image level1 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4); // 256 56
    Image level2 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Image level3 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Image victory = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4); // 288
    Image game_over = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);  //360

    TextureSet *hero;
    TextureSet *enemy_slime;
    TextureSet *enemy_skelly;
    TextureSet *enemy_goblin;
    TextureSet *enemy_voodoo;
    TextureSet *enemy_cultist;
    TextureSet *enemy_devil;
    TextureSet *enemy_angel;

};

#endif