#include "Player.h"
#include "config.h"
#include "Sprites.h"

Player::Player(Point position) : Entity(position) {
    Sprites *sprites = Sprites::GetInstance();
    textures = sprites->hero;
}

bool Player::move(MovementDir dir, char *grid) {
    int x = pos.x;
    int y = pos.y;
    bool moved = false;

    if (   (dir == MovementDir::UP    && y > 0             && grid[(y-1)*GRID_SIZE + x] != cwall)
        || (dir == MovementDir::DOWN  && y < GRID_SIZE - 1 && grid[(y+1)*GRID_SIZE + x] != cwall)
        || (dir == MovementDir::LEFT  && x > 0             && grid[y*GRID_SIZE + x - 1] != cwall)
        || (dir == MovementDir::RIGHT && x < GRID_SIZE - 1 && grid[y*GRID_SIZE + x + 1] != cwall)) {

        makeMove(dir);
        moved = true;
    }

    setDirection(dir);
    return moved;
}