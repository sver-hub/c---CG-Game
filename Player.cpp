#include "Player.h"
#include "config.h"

void Player::move(MovementDir dir, char *grid) {
    int x = pos.x;
    int y = pos.y;

    switch(dir){
        case MovementDir::UP:
            if (y > 0 && grid[(y-1)*GRID_SIZE + x] != '#') {
                updatePrevPos();
                pos.y--;
                animationState = 14;
            }
            break;

        case MovementDir::DOWN:
            if (y < GRID_SIZE - 1 && grid[(y+1)*GRID_SIZE + x] != '#') {
                updatePrevPos();
                pos.y++;
                animationState = 14;
            }
            break;

        case MovementDir::LEFT:
            if (x > 0 && grid[y*GRID_SIZE + x - 1] != '#') {
                turnDir = dir; 
                updatePrevPos();
                pos.x--;
                animationState = 14;
            }
            break;

        case MovementDir::RIGHT:
            if (x < GRID_SIZE - 1 && grid[y*GRID_SIZE + x + 1] != '#') {
                turnDir = dir;
                updatePrevPos();
                pos.x++;
                animationState = 14;
            }
            break;

        default:
            return;
      
    }

    direction = dir;
}