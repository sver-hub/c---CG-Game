#include "LightSource.h"
#include <vector>

class FireUrn: public LightSource {
    Image* texture;

    public:
    FireUrn(Point _pixelPos, int _radius = 40);

    void draw(Image &screen, CameraController camera);

};

