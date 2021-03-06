#ifndef ENTITY
#define ENTITY

#include "Image.h"
#include "config.h"
#include "TextureSet.h"
#include "Structures.h"
#include "CameraController.h"
#include <string>

class Field;

class Entity {

    protected:

    void makeMove(MovementDir dir);

    void setDirection(MovementDir dir);


    Point pos;
    Point prev_pos;
    std::string name;
    int maxHealth;
    int health;
    int attackDamage;
    MovementDir direction = MovementDir::LEFT;
    MovementDir turnDir = MovementDir::LEFT;
    TextureSet *textures;
    Field* field;
    int animationState = 0;
    int idleState = 0;
    int attackState = 0;
    int damagedState = 0;
    int deathState = 0;

    void updatePrevPos() { prev_pos.x = pos.x; prev_pos.y = pos.y; }

    public:

    Entity(Field* _field, Point position): pos(position), prev_pos(position), field(_field) {}

    ~Entity() {}

    Point getPos() { return pos; }

    int getAttackDamage() { return attackDamage; }

    bool isAlive() { return health > 0; }

    void takeDamage(int damage);

    bool attack(Point p);

    Point getSpritePos();

    Point getPrevPos() { return prev_pos; }

    bool looksLeft() { return turnDir == MovementDir::LEFT; }

    void draw(Image &screen, CameraController camera); 
    
    void drawAttack(Image &screen, CameraController camera);

    void displayHealth(Image& screen, CameraController camera);
};

#endif