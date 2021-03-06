#ifndef STRUCTURES
#define STRUCTURES

#include <stdlib.h>
#include <math.h>

struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    Point operator+(Point other) {
        return Point(this->x + other.x, this->y + other.y);
    }

    Point operator-(Point other) {
        return Point(this->x - other.x, this->y - other.y);
    }

    Point operator*(int k) {
        return Point(x * k, y * k);
    }

    void operator+=(Point other) {
        this->x += other.x;
        this->y += other.y;
    }

    void operator-=(Point other) {
        this->x -= other.x;
        this->y -= other.y;
    }

    bool operator==(Point other) {
        return this->x == other.x && this->y == other.y;
    }

    int distRaw(Point other) {
        return abs(this->x - other.x) + abs(this->y - other.y);
    }

    float dist(Point other) {
        return sqrtf(1.0f * (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

enum class MovementDir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

static Point dirToVec(MovementDir dir) {
    switch (dir)
    {
    case MovementDir::LEFT:
        return Point(-1, 0);

    case MovementDir::RIGHT:
        return Point(1, 0);
    
    case MovementDir::UP:
        return Point(0, -1);

    case MovementDir::DOWN:
        return Point(0, 1);
    
    default:
        break;
    }
    return Point(0 ,0);
}

static MovementDir randomDir() {
    return static_cast<MovementDir>(rand()%4);
}

#endif