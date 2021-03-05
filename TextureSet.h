#ifndef TEXTURESET
#define TEXTURESET

#include "Image.h"
#include "config.h"
#include <vector>

class TextureSet {

    Image bottom_r =        Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_r_idle_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_r_idle_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_r_idle_3 = Image(TILE_SIZE, TILE_SIZE, 4);

    Image top_r =           Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_r_idle_1 =    Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_r_idle_2 =    Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_r_idle_3 =    Image(TILE_SIZE, TILE_SIZE, 4);


    Image bottom_l =        Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_l_idle_1 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_l_idle_2 = Image(TILE_SIZE, TILE_SIZE, 4);
    Image bottom_l_idle_3 = Image(TILE_SIZE, TILE_SIZE, 4);

    Image top_l =           Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_l_idle_1 =    Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_l_idle_2 =    Image(TILE_SIZE, TILE_SIZE, 4);
    Image top_l_idle_3 =    Image(TILE_SIZE, TILE_SIZE, 4);

    Image attack_l_1 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_l_2 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_l_3 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_l_4 =      Image(TILE_SIZE, TILE_SIZE, 4);

    Image attack_t_1 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_t_2 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_t_3 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_t_4 =      Image(TILE_SIZE, TILE_SIZE, 4);

    Image attack_r_1 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_r_2 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_r_3 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_r_4 =      Image(TILE_SIZE, TILE_SIZE, 4);

    Image attack_d_1 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_d_2 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_d_3 =      Image(TILE_SIZE, TILE_SIZE, 4);
    Image attack_d_4 =      Image(TILE_SIZE, TILE_SIZE, 4);

    Image death_1 =         Image(TILE_SIZE, TILE_SIZE, 4);
    Image death_2 =         Image(TILE_SIZE, TILE_SIZE, 4);
    Image death_3 =         Image(TILE_SIZE, TILE_SIZE, 4);
    Image death_4 =         Image(TILE_SIZE, TILE_SIZE, 4);

    public:
    std::vector<Image*> bottom_left;
    std::vector<Image*> bottom_right;
    std::vector<Image*> top_left;
    std::vector<Image*> top_right;
    std::vector<Image*> attack_left;
    std::vector<Image*> attack_right;
    std::vector<Image*> attack_up;
    std::vector<Image*> attack_down;
    std::vector<Image*> death;

    TextureSet(Image &tiles, int body_x, int body_y, int attack_x, int attack_y) 
    {
        bottom_r.initTile(tiles, body_x, body_y);
        bottom_r_idle_1.initTile(tiles, body_x +   TILE_SIZE, body_y);
        bottom_r_idle_2.initTile(tiles, body_x + 2*TILE_SIZE, body_y);
        bottom_r_idle_3.initTile(tiles, body_x + 3*TILE_SIZE, body_y);
        bottom_right.push_back(&bottom_r);
        bottom_right.push_back(&bottom_r_idle_1);
        bottom_right.push_back(&bottom_r_idle_2);
        bottom_right.push_back(&bottom_r_idle_3);

        top_r.initTile(tiles, body_x, body_y + TILE_SIZE);
        top_r_idle_1.initTile(tiles, body_x +   TILE_SIZE, body_y + TILE_SIZE);
        top_r_idle_2.initTile(tiles, body_x + 2*TILE_SIZE, body_y + TILE_SIZE);
        top_r_idle_3.initTile(tiles, body_x + 3*TILE_SIZE, body_y + TILE_SIZE);
        top_right.push_back(&top_r);
        top_right.push_back(&top_r_idle_1);
        top_right.push_back(&top_r_idle_2);
        top_right.push_back(&top_r_idle_3);

        bottom_l.mirror(bottom_r);
        bottom_l_idle_1.mirror(bottom_r_idle_1);
        bottom_l_idle_2.mirror(bottom_r_idle_2);
        bottom_l_idle_3.mirror(bottom_r_idle_3);
        bottom_left.push_back(&bottom_l);
        bottom_left.push_back(&bottom_l_idle_1);
        bottom_left.push_back(&bottom_l_idle_2);
        bottom_left.push_back(&bottom_l_idle_3);

        top_l.mirror(top_r);
        top_l_idle_1.mirror(top_r_idle_1);
        top_l_idle_2.mirror(top_r_idle_2);
        top_l_idle_3.mirror(top_r_idle_3);
        top_left.push_back(&top_l);
        top_left.push_back(&top_l_idle_1);
        top_left.push_back(&top_l_idle_2);
        top_left.push_back(&top_l_idle_3);

        attack_r_1.initTile(tiles, attack_x, attack_y);
        attack_r_2.initTile(tiles, attack_x +   TILE_SIZE, attack_y);
        attack_r_3.initTile(tiles, attack_x + 2*TILE_SIZE, attack_y);
        attack_r_4.initTile(tiles, attack_x + 3*TILE_SIZE, attack_y);
        attack_right.push_back(&attack_r_1);
        attack_right.push_back(&attack_r_2);
        attack_right.push_back(&attack_r_3);
        attack_right.push_back(&attack_r_4);

        attack_t_1.turnRight(attack_r_1);
        attack_t_2.turnRight(attack_r_2);
        attack_t_3.turnRight(attack_r_3);
        attack_t_4.turnRight(attack_r_4);
        attack_up.push_back(&attack_t_1);
        attack_up.push_back(&attack_t_2);
        attack_up.push_back(&attack_t_3);
        attack_up.push_back(&attack_t_4);

        attack_l_1.mirror(attack_r_1);
        attack_l_2.mirror(attack_r_2);
        attack_l_3.mirror(attack_r_3);
        attack_l_4.mirror(attack_r_4);
        attack_left.push_back(&attack_l_1);
        attack_left.push_back(&attack_l_2);
        attack_left.push_back(&attack_l_3);
        attack_left.push_back(&attack_l_4);

        attack_d_1.turnLeft(attack_r_1);
        attack_d_2.turnLeft(attack_r_2);
        attack_d_3.turnLeft(attack_r_3);
        attack_d_4.turnLeft(attack_r_4);
        attack_down.push_back(&attack_d_1);
        attack_down.push_back(&attack_d_2);
        attack_down.push_back(&attack_d_3);
        attack_down.push_back(&attack_d_4);

        death_1.initTile(tiles, 224, 528);
        death_2.initTile(tiles, 224 +   TILE_SIZE, 528);
        death_3.initTile(tiles, 224 + 2*TILE_SIZE, 528);
        death_4.initTile(tiles, 224 + 3*TILE_SIZE, 528);
        death.push_back(&death_1);
        death.push_back(&death_2);
        death.push_back(&death_3);
        death.push_back(&death_4);
    }

};

#endif