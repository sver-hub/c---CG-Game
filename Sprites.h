#ifndef SPRITES
#define SPRITES

#include <string>
#include "Image.h"
#include "config.h"

class Sprites
{

protected:
    Sprites(){}

    static Sprites* singleton_;

public:

    Sprites(Sprites &other) = delete;
    
    void operator=(const Sprites &) = delete;
   
    static Sprites *GetInstance();

    void load(Image &tiles);

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

    Image hero_t = Image(TILE_SIZE, TILE_SIZE, 4);
    Image hero = Image(TILE_SIZE, TILE_SIZE, 4);
};

#endif