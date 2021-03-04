#ifndef CONFIG
#define CONFIG

#include "Image.h"

constexpr int TILE_SIZE = 16;
constexpr int GRID_SIZE = 48;

constexpr int SCREEN_HEIGHT = GRID_SIZE * TILE_SIZE;
constexpr int SCREEN_WIDTH = GRID_SIZE * TILE_SIZE;

constexpr int fps = 30;
constexpr float turnDelay = .3f;



constexpr char cwall = '#';
constexpr char cvoid = '.';
constexpr char cfloor = '_';
constexpr char cplayer = '@';
constexpr char cexit = 'x';
constexpr char ctrap = 'T';

constexpr Pixel empty{0, 0, 0, 0};
constexpr Pixel white{255, 255, 255, 255};
constexpr Pixel red{255, 0, 0, 255};
constexpr Pixel green{0, 255, 0, 255};
constexpr Pixel blue{0, 0, 255, 255};
constexpr Pixel yellow{255, 255, 0, 255};
constexpr Pixel violet{255, 0, 255, 255};

#endif