#include "LightSource.h"
#include "config.h"
#include <iostream>

LightSource::LightSource(Point _pos, int _radius): pos(_pos), ticker(fps), baseRadius(_radius), radius(_radius) {}

void LightSource::draw(Image &screen, CameraController camera) {
    if (!camera.isSpriteVisible(pos)) return;
    if (ticker % (fps/4) == 0) {
        radius = baseRadius - (rand()%(baseRadius/5));
        if (ticker == 0) ticker = 10;
    }
    
    for (int j = - radius; j <= radius; j++) {
        for (int i = - radius; i <= radius; i++) {
            int w = pos.x - camera.x0 + i + (SCREEN_WIDTH-2*camera.radius)/2;
            int h = pos.y - camera.y0 + j + (SCREEN_HEIGHT-2*camera.radius)/2 - TILE_SIZE;
            if (w < 0 || w > SCREEN_WIDTH || h < 0 || h > SCREEN_HEIGHT) continue;
            float dist = Point(w,h).dist(pos - Point(camera.x0, camera.y0 + TILE_SIZE));
            if (dist > radius) continue;
            if (screen.getPixel(w,h).isEmpty()) continue;
            Pixel p = white;
             p.g = (uint8_t)((1 - (dist/(2*radius))*(dist/(2*radius)))*255);
            p.b = (uint8_t)((1 - dist/(2*radius))*255);
            screen.addPixel(w, h, p, (1 - dist/(2*radius)));
        }
    }
    ticker--;
}


void LightSource::illuminate(Image &screen, CameraController camera) {
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            float dist = Point(i,j).dist(pos - Point(camera.x0, camera.y0));
            if (dist > radius*0.9f) 
                screen.multPixel(i, j, 0);
            else 
                screen.multPixel(i,j, (radius - dist) * (radius - dist) / (radius * radius));
        }
    }
}