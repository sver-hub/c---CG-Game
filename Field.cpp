#ifndef FIELD
#define FIELD

#include "Field.h"
#include <fstream>


Field::Field(const std::string &level): gridSize(GRID_SIZE), tileSize(TILE_SIZE) {
    grid = new char[gridSize*gridSize];
    sprites = Sprites::GetInstance();
    player.setTextures(sprites->hero, sprites->hero_t);

    srand((unsigned)time(NULL));

    char ch;
    std::fstream fin(level, std::fstream::in);
    int i = 0;
    while (fin >> std::noskipws >> ch) {
        if (ch == '\n') continue;
        grid[i++] = ch;
    }
    fin.close();

    initLevel();        
}

void Field::draw(Image &screen) {        
    for (int j = 0; j < screen.getHeight(); j++) {
        for (int i = 0; i < screen.getWidth(); i++) {
            screen.putPixel(i,j, level_l1.getPixel(i,j));
            Pixel pix = level_l2.getPixel(i,j);
            if (pix.r == 0 && pix.g == 0 && pix.b == 0 && pix.a == 0) continue;
            screen.putPixel(i,j, level_l2.getPixel(i,j));
        }
    }
}

void Field::redraw(Image &screen) {
    Point prev = player.getPrevPos();
    Point pos = player.getPos();

    redrawTile(screen, prev.x, prev.y, 1);
    redrawTile(screen, pos.x, pos.y, 1);

    player.draw(screen);

    redrawTile(screen, prev.x, prev.y, 2, false);
    redrawTile(screen, pos.x, pos.y, 2, false);
    

}

void Field::redrawTile(Image &screen, int x, int y, int layer, bool clear) {
    if (clear) {
        screen.clearTile(x, y);
        screen.clearTile(x, y-1);
    }
    if (layer == 1) {
        screen.putTile(x, y, level_l1, x, y);
        screen.putTile(x, y-1, level_l1, x, y-1);
    } else if (layer == 2) {
        screen.putTile(x, y, level_l2, x, y);
        screen.putTile(x, y-1, level_l2, x, y-1);
    }
}

void Field::initLevel() {
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            char c = grid[y*gridSize + x];
            if (c == '_') {
                putFloor(x, y);
            } else if (c == '#') {
                putWall(x, y);
            } else if (c == '.') {
                putVoid(x, y);
            }     
        }
    } 
}

char* Field::getNeighbors(int x, int y) {
    //[7][0][4]
    //[3][_][1]
    //[6][2][5]
    char *res = (char*)malloc(8*sizeof(char));
    bool t = y > 0;
    bool r = x < gridSize - 1;
    bool b = y < gridSize - 1;
    bool l = x > 0;

        
    res[0] = t ? grid[(y - 1) * gridSize + x] : 'q';
    res[1] = r ? grid[y * gridSize + x + 1] : 'q';
    res[2] = b ? grid[(y + 1) * gridSize + x] : 'q';
    res[3] = l ? grid[y * gridSize + x - 1] : 'q';
    res[4] = (t && r) ? grid[(y - 1) * gridSize + x + 1] : 'q';
    res[5] = (b && r) ? grid[(y + 1) * gridSize + x + 1] : 'q';
    res[6] = (b && l) ? grid[(y + 1) * gridSize + x - 1] : 'q';
    res[7] = (t && l) ? grid[(y - 1) * gridSize + x - 1] : 'q';

    return res;
}

void Field::putVoid(int x, int y) {
    char *neig = getNeighbors(x, y);

    if (neig[2] == '#' && !(neig[6] == '.' || neig[5] == '.')) 
        level_l2.putTile(x,y, sprites->wall_t);

    free(neig);
}

void Field::putFloor(int x, int y) {
    char *neig = getNeighbors(x, y);

    int k = rand()%100;
    if (k < 40)
        level_l1.putTile(x,y, sprites->floor);
    else if (k < 60)
        level_l1.putTile(x,y, sprites->floor_crack1);
    else if (k < 80)
        level_l1.putTile(x,y, sprites->floor_crack2);
    else if (k < 97)
        level_l1.putTile(x,y, sprites->floor_crack3);
    else if (k < 98)
        level_l1.putTile(x,y, sprites->floor_crack4);
    else if (k < 99)
        level_l1.putTile(x,y, sprites->floor_crack_left);
    else 
        level_l1.putTile(x,y, sprites->floor_crack_right);

    if (neig[2] == '#') 
        level_l2.putTile(x,y, sprites->wall_t);

    free(neig);
}

void Field::putWall(int x, int y) {
    char *neig = getNeighbors(x, y);
        
    if (neig[3] == '.')
        if (neig[2] == '.')
            level_l1.putTile(x,y, sprites->wall_side_rb);
        else
            level_l1.putTile(x,y, sprites->wall_side_r);
    else if (neig[1] == '.')
        if (neig[2] == '.')
            level_l1.putTile(x,y, sprites->wall_side_lb);
        else
            level_l1.putTile(x,y, sprites->wall_side_l);
    else {
        int k = rand()%100;
        if (k < 96)
            level_l1.putTile(x,y, sprites->wall);
        else if (k < 98)
            level_l1.putTile(x, y, sprites->wall_hole1);
        else
            level_l1.putTile(x, y, sprites->wall_hole2);    
    }


    if ((neig[3] == '#' && neig[5] == '#' && neig[1] == '_')
            || (neig[3] == '#' && neig[5] == '_' && neig[1] == '_')
            && neig[2] == '#')
        level_l1.putTile(x,y, sprites->wall_side_r);
    else if ((neig[1] == '#' && neig[6] == '#' && neig[3] == '_')
            || (neig[1] == '#' && neig[6] == '_' && neig[3] == '_') 
            && neig[2] == '#')
        level_l1.putTile(x,y, sprites->wall_side_l);


    if (((neig[1] == '#' && neig[6] == '#' && neig[3] == '.') 
            || (neig[3] == '#' && neig[5] == '#' && neig[1] == '.')
            || (neig[3] == '_' && neig[5] == '#' && neig[1] == '.')
            || (neig[1] == '_' && neig[6] == '#' && neig[3] == '.')) 
            && neig[2] == '#')
        level_l2.putTile(x,y, sprites->wall_t);

    free(neig);
}


#endif