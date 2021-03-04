#include "FireUrn.h"
#include "Sprites.h"

FireUrn::FireUrn(Point _pixelPos, int _radius): LightSource(_pixelPos, _radius) {
    Sprites *sprites = Sprites::GetInstance();
    texture = &sprites->fire;
}

void FireUrn::draw(Image &screen, CameraController camera) {
    LightSource::draw(screen, camera);
    screen.putSprite(pos.x - TILE_SIZE/2, pos.y - 4, *texture, camera);
}

