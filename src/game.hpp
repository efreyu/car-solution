/* Created by efreyu on 22.05.2020. */
#include <iostream>
#include <cstdlib>
#include <vector>

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

class Collision {
public:
    static bool AABB(const sTransform &transformA, const sTransform &transformB) {
        return transformA.x + transformA.width >= transformB.x &&
               transformB.x + transformB.width >= transformA.x &&
               transformA.y + transformA.height >= transformB.y &&
               transformB.y + transformB.height >= transformA.y;
    }
};
