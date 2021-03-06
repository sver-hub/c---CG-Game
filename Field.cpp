#ifndef FIELD
#define FIELD

#include "Field.h"
#include <fstream>
#include <iostream>


Field::Field(const std::string &level, int en_count[6]): gridSize(GRID_SIZE), tileSize(TILE_SIZE), visionRadius(300) {
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
    spawnEnemies(en_count);     
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
            if (!enemy->isAlive()) continue;
            enemy->move();
            checkTraps(enemy->getPos());
        }
    }
}

void Field::draw(Image &screen) {   
    Point playerSpritePos = player->getSpritePos();
    camera.calculate(playerSpritePos, visionRadius);
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            if (camera.isVisible(Point(camera.x0 + i, camera.y0 + j)))
                screen.putPixel(i + (SCREEN_WIDTH-2*visionRadius)/2, j + (SCREEN_HEIGHT- 2*visionRadius)/2,
                                level_l1.getPixel(camera.x0 + i,camera.y0 +j));
        }
    }

    for (const auto &trap: traps) {
        trap->draw(screen, camera);
    }

    player->draw(screen, camera);

    for (const auto &enemy : enemies) {
        enemy->draw(screen, camera);
    }

    player->drawAttack(screen, camera);

    for (const auto &enemy : enemies) {
        enemy->drawAttack(screen, camera);
    }

    for (const auto &ls : lightSources) {
        ls->draw(screen, camera);
    }

    player->displayHealth(screen, camera);

    for (const auto &enemy : enemies) {
        if (enemy->isAlive())
            enemy->displayHealth(screen, camera);
    }

    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            if (level_l2.getPixel(camera.x0 + i, camera.y0 + j).isEmpty()) continue;

            if (camera.isVisible(Point(camera.x0 + i, camera.y0 + j)))
                screen.putPixel(i + (SCREEN_WIDTH-2*visionRadius)/2, j + (SCREEN_HEIGHT- 2*visionRadius)/2, 
                                level_l2.getPixel(camera.x0 + i,camera.y0 +j));
        }
    }

    LightSource(playerSpritePos, visionRadius).illuminate(screen, camera);
}

bool Field::isValid(Point p) {
    if (p.x >= 0 && p.x < GRID_SIZE && p.y >= 0 && p.y < GRID_SIZE 
            && grid[p.y * GRID_SIZE + p.x] != cwall 
            && grid[p.y * GRID_SIZE + p.x] != cvoid
            && grid[p.y * GRID_SIZE + p.x] != clight)
    {
        if (isPlayer(p) || isEnemy(p)) return false;

        return true;
    }
    return false;
    
}

bool Field::isPlayer(Point p) {
    return p == player->getPos();
}

bool Field::isEnemy(Point p) {
    for (const auto &enemy : enemies) {
        if (p == enemy->getPos()) 
            return true;
    } 
    return false; 
}

bool Field::isTrap(Point p) {
    for (const auto &trap : traps) {
        if (p == trap->getPos()) 
            return true;
    } 
    return false; 
}

Entity* Field::getEntityAtPos(Point p) {
    if (isPlayer(p)) return player;
    for (const auto &enemy : enemies) {
        if (p == enemy->getPos()) 
            return enemy;
    }
    return nullptr;
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
            } else if (c == clight) {
                putFloor(x,y);
                lightSources.push_back(
                    new FireUrn(Point(x * TILE_SIZE + TILE_SIZE/2, (GRID_SIZE - y) * TILE_SIZE + TILE_SIZE/2)));
            }
        }
    } 
}

void Field::spawnEnemies(int en_count[6]) {
    // skelly slime goblin voodoo cultist devil

    for (int i = 0; i < 6; i++) {
        for (int j = en_count[i]; j >0; j--) {
            Enemy *en;
            if (i == 0) en = new Enemy_Skelly(this);
            else if (i == 1) en = new Enemy_Slime(this);
            else if (i == 2) en = new Enemy_Goblin(this);
            else if (i == 3) en = new Enemy_Voodoo(this);
            else if (i == 4) en = new Enemy_Cultist(this);
            else if (i == 5) en = new Enemy_Devil(this);

            if (en->spawn()) {
                enemies.push_back(en);
            }
            else {
                delete en;
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
            || (neig[3] == cwall && (neig[5] == cfloor || neig[5] == ctrap) 
            && (neig[1] == cfloor || neig[1] == ctrap))
            && neig[2] == cwall)
        level_l1.putTile(x,y, sprites->wall_side_r);
    else if ((neig[1] == cwall && neig[6] == cwall && neig[3] == cfloor)
            || (neig[1] == cwall && (neig[6] == cfloor || neig[6] == ctrap) 
            && (neig[3] == cfloor || neig[3] == ctrap)) 
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