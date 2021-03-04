#include "Image.h"
#include <vector>
#include "Sprites.h"
#include "Structures.h"
#include "CameraController.h"

class Trap {
    Point pos;
    std::vector<Image*> textures;
    int activated = 0;

    public:
    Trap(Point position);

    Point getPos() { return pos; }

    bool check(Point p, int num_ent);

    void draw(Image &screen, CameraController camera);

};