#include "LightSource.h"
#include "config.h"
#include <iostream>

LightSource::LightSource(Point _pos, int _radius): pos(_pos), ticker(fps), baseRadius(_radius), radius(_radius) {}

void LightSource::draw(Image &screen, CameraController camera) {
    if (!camera.isSpriteVisible(pos * TILE_SIZE)) return;
    int x = pos.x * TILE_SIZE;
    int y = pos.y * TILE_SIZE;
    if (ticker % (fps/4) == 0) {
        radius = baseRadius - (rand()%(baseRadius/5));
        if (ticker == 0) ticker = 10;
    }
    for (int j = y - radius; j <= y + radius; j++) {
        for (int i = x - radius; i <= x + radius; i++) {
            float dist = Point(i,j).dist(Point(x,y));
            if (dist > radius) continue;
            Pixel pix = screen.getPixel(i,j);
            if (pix.r == 0 && pix.g == 0 && pix.b == 0 && pix.a == 0) continue;
            Pixel p = yellow;
            p.g = (uint8_t)((1 - dist/(2*radius))*255);
            screen.addPixel(i, j, p, (1 - dist/(2*radius)));
        }
    }
    ticker--;
}

void LightSource::clear(Image &screen, Image &field) {
    int x = pos.x * TILE_SIZE;
    int y = pos.y * TILE_SIZE;
    for (int j = y - baseRadius; j <= y + baseRadius; j++) {
        for (int i = x - baseRadius; i <= x + baseRadius; i++) {
            if (Point(i,j).dist(Point(x,y)) > baseRadius) continue;
            screen.putPixel(i,j, field.getPixel(i,j));
        }
    }
}