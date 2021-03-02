#ifndef FIELD_1
#define FIELD_1

#include "Image.h"
#include "config.h"
#include "Sprites.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"
#include "Enemy_Slime.h"

class Field {
    char *grid;
    int gridSize;
    int tileSize;
    Sprites *sprites;
    Image level_l1 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Image level_l2 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Point starting_pos{.x = GRID_SIZE - 3, .y = GRID_SIZE -3};
	Player player = Player(starting_pos);
    std::vector<Enemy*> enemies;

    void spawnEnemies();

    void redrawLayer(Image &screen, int layer);

    void redrawTile(Image &screen, int x, int y, int layer, bool clear = true);

    public:
    Field(const std::string &level);

    ~Field() { delete grid; }

    Player getPlayer() { return player; }

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

    

};

#endif