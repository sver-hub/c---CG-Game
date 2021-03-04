#include "Structures.h"
#include "Image.h"

class LightSource {
    Point pos;
    int baseRadius;
    int radius;
    float intensity;
    int ticker;

    public:
    LightSource(Point _pos, int _radius = 20);

    void draw(Image &screen);

    void clear(Image &screen, Image &field);
};