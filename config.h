#ifndef CONFIG
#define CONFIG

#include "Image.h"

constexpr int SCREEN_HEIGHT = 512;
constexpr int SCREEN_WIDTH = 512;

constexpr int TILE_SIZE = 16;
constexpr int GRID_SIZE = 32;

constexpr int fps = 30;
constexpr float turnDelay = .3f;

constexpr Pixel empty{0, 0, 0, 0};
constexpr Pixel white{255, 255, 255, 255};
constexpr Pixel red{255, 0, 0, 255};
constexpr Pixel green{0, 255, 0, 255};
constexpr Pixel blue{0, 0, 255, 255};
constexpr Pixel violet{255, 0, 255, 255};

#endif