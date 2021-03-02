#ifndef FIELD_1
#define FIELD_1

#include "Image.h"
#include "config.h"
#include "Sprites.h"
#include "Player.h"
#include <vector>
#include "Trap.h"
#include "Enemy.h"
#include "Enemy_Slime.h"
#include "Enemy_Angel.h"
#include "Enemy_Cultist.h"
#include "Enemy_Devil.h"
#include "Enemy_Skelly.h"
#include "Enemy_Voodoo.h"
#include "Enemy_Goblin.h"

class Field {
    char *grid;
    int gridSize;
    int tileSize;
    Sprites *sprites;
    Image level_l1 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Image level_l2 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
	Player *player;
    std::vector<Enemy*> enemies;
    std::vector<Trap*> traps;

    void spawnEnemies();

    void redrawLayer(Image &screen, int layer);

    void redrawTile(Image &screen, int x, int y, int layer, bool clear = true);

    public:
    Field(const std::string &level);

    ~Field() { delete grid; }

    Player* getPlayer() { return player; }

    char* getGrid() { return grid; }

    std::vector<Enemy*> getEnemies() { return enemies; }

    void ProcessInput(MovementDir dir);

    void draw(Image &screen);

    void redraw(Image &screen);

    bool isValid(Point p);

    private:

    void initLevel();

    char* getNeighbors(int x, int y);     

    void putVoid(int x, int y);

    void putFloor(int x, int y);

    void putWall(int x, int y);

    void putTrap(int x, int y);

};

#endif