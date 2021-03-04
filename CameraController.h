#ifndef CAMERACONTROLLER
#define CAMERACONTROLLER

#include "Structures.h"
#include "config.h"

struct CameraController {
    int x0;
    int y0;
    int x1;
    int y1;
    int radius;

    CameraController() {}

    void calculate(Point playerSpritePos, int visionRadius) {
        int dx0 = std::min(playerSpritePos.x - visionRadius, 0);
        int dy0 = std::min(playerSpritePos.y - visionRadius, 0);
        int dx1 = std::max(playerSpritePos.x + visionRadius - (GRID_SIZE - 1) * TILE_SIZE, 0);
        int dy1 = std::max(playerSpritePos.y + visionRadius - (GRID_SIZE - 1) * TILE_SIZE, 0);
        x0 = std::max(playerSpritePos.x - visionRadius, 0) - dx1;
        y0 = std::max(playerSpritePos.y - visionRadius, 0) - dy1;
        x1 = std::min(playerSpritePos.x + visionRadius, (GRID_SIZE - 1) * TILE_SIZE) - dx0;
        y1 = std::min(playerSpritePos.y + visionRadius, (GRID_SIZE - 1) * TILE_SIZE) - dy0;
        radius = visionRadius;

    }

    bool isVisible(Point p) {
        return p.x > x0 && p.x < x1 && p.y > y0 && p.y < y1;
    }

    bool isSpriteVisible(Point spritePos) {
        return ((spritePos.x + TILE_SIZE > x0  && spritePos.x + TILE_SIZE < x1) 
                || (spritePos.x > x0  && spritePos.x < x1)) 
        && ((spritePos.y + TILE_SIZE > y0  && spritePos.y + TILE_SIZE < y1) 
                || (spritePos.y > y0  && spritePos.y < y1))
        && (spritePos.x >= 0 && spritePos.x < GRID_SIZE*TILE_SIZE && spritePos.y >= 0 && spritePos.y < GRID_SIZE * TILE_SIZE);
    }
};

#endif