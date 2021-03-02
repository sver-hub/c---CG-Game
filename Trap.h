#include "Image.h"
#include <vector>
#include "Sprites.h"

class Trap {
    Point pos;
    std::vector<Image*> textures;

    public:
    Trap(Point position);

    void draw(Image &screen);


};