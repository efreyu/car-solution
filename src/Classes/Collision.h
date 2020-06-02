#ifndef CAR_EXAMPLE_COLLISION_H
#define CAR_EXAMPLE_COLLISION_H

#include "sTransform.h"
#include <cmath>

class Collision {
public:
    /*
     * Axis-aligned bounding boxes (AABB) are the quickest algorithm
     * to determine whether the two game entities are overlapping or not.
     */
    static bool AABB(const sTransform &transformA, const sTransform &transformB, const int &padding = 0) {
        return GetRotatedX(transformA) + (transformA.width * transformA.scale) + padding >= GetRotatedX(transformB) &&
               GetRotatedX(transformB) + (transformB.width * transformB.scale) + padding >= GetRotatedX(transformA) &&
               GetRotatedY(transformA) + (transformA.height * transformA.scale) + padding >= GetRotatedY(transformB) &&
               GetRotatedY(transformB) + (transformB.height * transformB.scale) + padding >= GetRotatedY(transformA);
    }

protected:

    static float Theta(const double &angle) {
        return (float)(angle / 180 * M_PI);
    }

    static float GetRotatedX(const sTransform &transform) {
        if (transform.angle == 0.0) {
            return (float)transform.x;
        }
        float tempX = transform.x - (transform.x + (transform.width * transform.scale / 2));
        float tempY = transform.y - (transform.y + (transform.height * transform.scale / 2));
        return (float)(tempX * cos(Theta(transform.angle)) - tempY * sin(Theta(transform.angle))) + (transform.x + (transform.width * transform.scale / 2));
    }

    static float GetRotatedY(const sTransform &transform) {
        if (transform.angle == 0.0) {
            return (float)transform.y;
        }
        float tempX = transform.x - (transform.x + (transform.width * transform.scale / 2));
        float tempY = transform.y - (transform.y + (transform.height * transform.scale / 2));
        return (float)(tempX * sin(Theta(transform.angle)) + tempY * cos(Theta(transform.angle))) + (transform.y + (transform.height * transform.scale / 2));
    }
};

#endif //CAR_EXAMPLE_COLLISION_H
