#ifndef LIGHTSOURCE
#define LIGHTSOURCE

#include "Structures.h"
#include "Image.h"
#include "CameraController.h"

class LightSource {
    protected:
    Point pos;
    int baseRadius;
    int radius;
    float intensity;
    int ticker;

    public:
    LightSource(Point _pixelPos, int _radius = 20);

    void draw(Image &screen, CameraController camera);

    void illuminate(Image &screen, CameraController camera);
};

#endif