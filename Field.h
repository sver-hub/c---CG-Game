#ifndef FIELD_1
#define FIELD_1

#include "Image.h"
#include "config.h"
#include "Sprites.h"
#include "Player.h"
#include <vector>
#include "CameraController.h"
#include "LightSource.h"
#include "Trap.h"
#include "Enemy.h"
#include "Enemy_Slime.h"
#include "Enemy_Cultist.h"
#include "Enemy_Devil.h"
#include "Enemy_Skelly.h"
#include "Enemy_Voodoo.h"
#include "Enemy_Goblin.h"
#include "FireUrn.h"

class Field {
    char *grid;
    int gridSize;
    int tileSize;
    int visionRadius;
    CameraController camera;
    Sprites *sprites;
    Image level_l1 = Image(GRID_SIZE * TILE_SIZE, GRID_SIZE * TILE_SIZE, 4);
    Image level_l2 = Image(GRID_SIZE * TILE_SIZE, GRID_SIZE * TILE_SIZE, 4);
	Player *player;
    std::vector<Enemy*> enemies;
    std::vector<Trap*> traps;
    std::vector<FireUrn*> lightSources;
    
    Point exitPos = Point(0,0);
    bool exited = false;

    void spawnEnemies(int en_count[6]);

    public:
    Field(const std::string &level, int en_count[6]);

    ~Field();

    Player* getPlayer() { return player; }

    char* getGrid() { return grid; }

    std::vector<Enemy*> getEnemies() { return enemies; }

    void ProcessInput(MovementDir dir);

    void draw(Image &screen);


    bool isValid(Point p);

    bool isEnemy(Point p);

    bool isPlayer(Point p);

    bool isTrap(Point p);

    Entity* getEntityAtPos(Point p);

    bool isExited() { return exited; };

    bool isDead() { return !player->isAlive(); }

    private:

    void initLevel();

    char* getNeighbors(int x, int y);     

    void putVoid(int x, int y);

    void putFloor(int x, int y);

    void putWall(int x, int y);

    void putTrap(int x, int y);

    void checkTraps(Point p);

};

#endif