/* Created by efreyu on 22.05.2020. */
#include <iostream>
#include <cstdlib>
#include <vector>

struct sPos {
public:
    int x;
    int y;
    sPos() { x = 0; y = 0; }
    sPos(int aX, int aY) { x = aX; y = aY; }
};

struct sSize
{
public:
    int width;
    int height;
    sSize() { width = 0; height = 0; }
    sSize(int aW, int aH) { width = aW; height = aH; }
};

struct sRect
{
public:
    sPos pos;
    sSize size;
    sRect() {};
    sRect(int x, int y, int w, int h) { pos.x = x; pos.y = y; size.width = w; size.height = h; }
    bool intersects(const sRect& other) {
        return other.pos.x + other.size.width >= pos.x &&
               pos.x + size.width >= other.pos.x &&
               other.pos.y + other.pos.x >= pos.y &&
               pos.y + size.height >= other.pos.y;
//        return !((other.pos.x + other.size.width <= pos.x) ||
//                 (other.pos.y + other.size.height <= pos.y) ||
//                 (other.pos.x >= pos.x + size.width) ||
//                 (other.pos.y >= pos.y + size.height));
    }
};

struct sTransform {
public:
    int x, y, width, height;

    sTransform() { x = y = width = height = 0; }
    sTransform(int transformX, int transformY, int transformWidth, int transformHeight)
        : x(transformX)
        , y(transformY)
        , width(transformWidth)
        , height(transformHeight)
        {};
};
