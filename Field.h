#include "Image.h"
#include "config.h"
#include "Sprites.h"
#include "Player.h"

class Field {
    char *grid;
    int gridSize;
    int tileSize;
    Sprites *sprites;
    Image level_l1 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Image level_l2 = Image(SCREEN_WIDTH, SCREEN_HEIGHT, 4);
    Point starting_pos{.x = GRID_SIZE - 3, .y = GRID_SIZE -3};
	Player player = Player(starting_pos);


    public:
    Field(const std::string &level);

    ~Field() { delete grid; }

    Player getPlayer() { return player; }

    void ProcessInput(MovementDir dir) { player.move(dir, grid); }

    void draw(Image &screen);

    void redraw(Image &screen);

    private:
    void initLevel();

    char* getNeighbors(int x, int y);     

    void putVoid(int x, int y);

    void putFloor(int x, int y);

    void putWall(int x, int y);

    void redrawTile(Image &screen, int x, int y, int layer, bool clear = true);

};