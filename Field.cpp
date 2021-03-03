#ifndef FIELD
#define FIELD

#include "Field.h"
#include <fstream>
#include <iostream>


Field::Field(const std::string &level): gridSize(GRID_SIZE), tileSize(TILE_SIZE) {
    grid = new char[gridSize*gridSize];
    enemies = std::vector<Enemy*>();
    traps = std::vector<Trap*>();
    sprites = Sprites::GetInstance();

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
    spawnEnemies();     
}

Field::~Field() {
    delete grid;
}

void Field::ProcessInput(MovementDir dir) {
    if (player->move(dir)) {
        if (exitPos == player->getPos()) {
            exited = true;
            return;
        }
        checkTraps(player->getPos());
        for (const auto &enemy : enemies) {
            enemy->move();
            checkTraps(enemy->getPos());
        }
    }
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
    redrawLayer(screen, 1);

    for (const auto &trap: traps) {
        trap->draw(screen);
    }

    player->draw(screen);

    for (const auto &enemy : enemies) {
        enemy->draw(screen);
    }

    redrawLayer(screen, 2);
    
}

void Field::redrawLayer(Image &screen, int layer_n) {
    Point prev = player->getPrevPos();
    Point pos = player->getPos();
    bool clear = layer_n == 1;
    redrawTile(screen, prev.x, prev.y, layer_n, clear);
    redrawTile(screen, pos.x, pos.y, layer_n, clear);

    // std::cout << enemies.size() << std::endl;
    for (const auto &enemy : enemies) {
        Point e_pos = enemy->getPos();
        Point e_prev_pos = enemy->getPrevPos();
        redrawTile(screen, e_pos.x, e_pos.y, layer_n, clear);
        redrawTile(screen, e_prev_pos.x, e_prev_pos.y, layer_n, clear);
    }
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

bool Field::isValid(Point p) {
    std::cout << this->enemies.size() << std::endl;
    if (p.x >= 0 && p.x < GRID_SIZE && p.y >= 0 && p.y < GRID_SIZE 
            && grid[p.y * GRID_SIZE + p.x] != cwall 
            && grid[p.y * GRID_SIZE + p.x] != cvoid)
    {
        // std::cout << player->getPos().x << " " << player->getPos().y << std::endl;
        if (p == player->getPos()) return false;

        for (const auto &enemy : enemies) {
            // std::cout << enemy->getPos().x << " " << enemy->getPos().y << std::endl;
            if (p == enemy->getPos()) return false;
        }
        return true;
    }
    return false;
    
}

void Field::initLevel() {
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            char c = grid[y*gridSize + x];
            if (c == cfloor) {
                putFloor(x, y);
            } else if (c == cwall) {
                putWall(x, y);
            } else if (c == cvoid) {
                putVoid(x, y);
            } else if (c == cplayer) {
                player = new Player(this, Point(x, y));
                putFloor(x, y);
            } else if (c == ctrap) {
                putTrap(x, y);
            } else if (c == cexit) {
                exitPos.x = x;
                exitPos.y = y;
                level_l1.putTile(x, y, sprites->exit);
            }
        }
    } 
}

void Field::spawnEnemies() {
    for (int i = 0; i < 10; i++) {
        Enemy *sl;
        if (i < 2) sl = new Enemy_Slime(this);
        else if (i < 4) sl = new Enemy_Goblin(this);
        else if (i < 6) sl = new Enemy_Skelly(this);
        else if (i < 7) sl = new Enemy_Voodoo(this);
        else if (i < 8) sl = new Enemy_Cultist(this);
        else if (i < 9) sl = new Enemy_Devil(this);
        else if (i < 10) sl = new Enemy_Angel(this);

        if (sl->spawn()) {
            enemies.push_back(sl);
        }
        else {
            delete sl;
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

    if (neig[2] == cwall && !(neig[6] == cvoid || neig[5] == cvoid)) 
        level_l2.putTile(x,y, sprites->wall_t);

    free(neig);
}

void Field::putFloor(int x, int y) {
    char *neig = getNeighbors(x, y);

    int k = rand()%100;
    if (k < 55)
        level_l1.putTile(x,y, sprites->floor);
    else if (k < 75)
        level_l1.putTile(x,y, sprites->floor_crack1);
    else if (k < 95)
        level_l1.putTile(x,y, sprites->floor_crack2);
    else if (k < 97)
        level_l1.putTile(x,y, sprites->floor_crack3);
    else if (k < 98)
        level_l1.putTile(x,y, sprites->floor_crack4);
    else if (k < 99)
        level_l1.putTile(x,y, sprites->floor_crack_left);
    else 
        level_l1.putTile(x,y, sprites->floor_crack_right);

    if (neig[2] == cwall) 
        level_l2.putTile(x,y, sprites->wall_t);

    free(neig);
}

void Field::putWall(int x, int y) {
    char *neig = getNeighbors(x, y);
        
    if (neig[3] == cvoid)
        if (neig[2] == cvoid)
            level_l1.putTile(x,y, sprites->wall_side_rb);
        else
            level_l1.putTile(x,y, sprites->wall_side_r);
    else if (neig[1] == cvoid)
        if (neig[2] == cvoid)
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


    if ((neig[3] == cwall && neig[5] == cwall && neig[1] == cfloor)
            || (neig[3] == cwall && neig[5] == cfloor && neig[1] == cfloor)
            && neig[2] == cwall)
        level_l1.putTile(x,y, sprites->wall_side_r);
    else if ((neig[1] == cwall && neig[6] == cwall && neig[3] == cfloor)
            || (neig[1] == cwall && neig[6] == cfloor && neig[3] == cfloor) 
            && neig[2] == cwall)
        level_l1.putTile(x,y, sprites->wall_side_l);


    if (((neig[1] == cwall && neig[6] == cwall && neig[3] == cvoid) 
            || (neig[3] == cwall && neig[5] == cwall && neig[1] == cvoid)
            || (neig[3] == cfloor && neig[5] == cwall && neig[1] == cvoid)
            || (neig[1] == cfloor && neig[6] == cwall && neig[3] == cvoid)) 
            && neig[2] == cwall)
        level_l2.putTile(x,y, sprites->wall_t);

    free(neig);
}


void Field::putTrap(int x, int y) {
    Trap *t = new Trap(Point(x, y));
    traps.push_back(t);
}

void Field::checkTraps(Point p) {
    for (const auto &trap : traps) {
        trap->check(p, enemies.size() + 1);
    }

}

#endif