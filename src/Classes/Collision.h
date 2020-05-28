#ifndef CAR_EXAMPLE_COLLISION_H
#define CAR_EXAMPLE_COLLISION_H

#include "sTransform.h"

class Collision {
public:
    /*
     * Axis-aligned bounding boxes (AABB) are the quickest algorithm
     * to determine whether the two game entities are overlapping or not.
     */
    static bool AABB(const sTransform &transformA, const sTransform &transformB) {
        return transformA.x + transformA.width >= transformB.x &&
               transformB.x + transformB.width >= transformA.x &&
               transformA.y + transformA.height >= transformB.y &&
               transformB.y + transformB.height >= transformA.y;
    }
};

#endif //CAR_EXAMPLE_COLLISION_H
