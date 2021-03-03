#ifndef TEXTURESET
#define TEXTURESET

#include "Image.h"
#include "config.h"

class TextureSet {

    public:
    Image bottom_r = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_r_idle_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_r_idle_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_r_idle_3 = Image(TILE_SIZE, TILE_SIZE, 4);

    Image top_r = Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_r_idle_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_r_idle_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_r_idle_3 = Image(TILE_SIZE, TILE_SIZE, 4);


    Image bottom_l = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_l_idle_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_l_idle_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_l_idle_3 = Image(TILE_SIZE, TILE_SIZE, 4);

    Image top_l = Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_l_idle_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_l_idle_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_l_idle_3 = Image(TILE_SIZE, TILE_SIZE, 4);

    TextureSet(Image &tiles, int x, int y) 
    {
        bottom_r.initTile(tiles, x, y);
        bottom_r_idle_1.initTile(tiles, x +   TILE_SIZE, y);
        bottom_r_idle_2.initTile(tiles, x + 2*TILE_SIZE, y);
        bottom_r_idle_3.initTile(tiles, x + 3*TILE_SIZE, y);

        top_r.initTile(tiles, x, y + TILE_SIZE);
        top_r_idle_1.initTile(tiles, x +   TILE_SIZE, y + TILE_SIZE);
        top_r_idle_2.initTile(tiles, x + 2*TILE_SIZE, y + TILE_SIZE);
        top_r_idle_3.initTile(tiles, x + 3*TILE_SIZE, y + TILE_SIZE);

        bottom_l.mirror(bottom_r);
        bottom_l_idle_1.mirror(bottom_r_idle_1);
        bottom_l_idle_2.mirror(bottom_r_idle_2);
        bottom_l_idle_3.mirror(bottom_r_idle_3);

        top_l.mirror(top_r);
        top_l_idle_1.mirror(top_r_idle_1);
        top_l_idle_2.mirror(top_r_idle_2);
        top_l_idle_3.mirror(top_r_idle_3);
    }

};

#endif