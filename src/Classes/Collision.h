#ifndef CAR_EXAMPLE_COLLISION_H
#define CAR_EXAMPLE_COLLISION_H

#include "sTransform.h"
#include <cmath>

namespace Collisions {
    struct Point {
        float x;
        float y;
        Point() { x = 0; y = 0; };
        Point(float x, float y) : x(x), y(y) {};
    };
};
using Collisions::Point;
using Rect = std::vector<Point>;

class Collision {
public:
    /*
     * Axis-aligned bounding boxes (AABB) are the quickest algorithm
     * to determine whether the two game entities are overlapping or not.
     */
    static bool AABB(const sTransform &transformA, const sTransform &transformB) {
        if ((transformA.angle == 0.0 || (int)std::abs(transformA.angle) % 180 == 0) &&
            (transformB.angle == 0.0 || (int)std::abs(transformB.angle) % 180 == 0)) {
            return transformA.x + transformA.width * transformA.scale >= transformB.x &&
                   transformB.x + transformB.width * transformB.scale >= transformA.x &&
                   transformA.y + transformA.height * transformA.scale >= transformB.y &&
                   transformB.y + transformB.height * transformB.scale >= transformA.y;
        }
        /*
         * When both rectangles have a rotation angle, the vertex detection algorithm
         * is used to check the intersection of the planes
         */
        return HasVortexIntersection(GetRect(transformA), GetRect(transformB));
    }

protected:

    static float Theta(const double &angle) {
        return (float)(angle / 180 * M_PI);
    }

    static Point GetCenter(const sTransform &transform) {
        return Point(transform.x + (transform.width * transform.scale / 2),
                transform.y + (transform.height * transform.scale / 2)
                );
    }

    static Rect GetRect(const sTransform &transform) {
        Rect rect{};
        // 1. default coordinates when the angle of the rectangle is zero or the remainder of dividing the angle by 180 is 0
        if (transform.angle == 0.0 || (int)std::abs(transform.angle) % 180 == 0) {
            //top right
            rect.emplace_back(Point(transform.x + transform.width * transform.scale, transform.y));
            //top left
            rect.emplace_back(Point(transform.x, transform.y));
            //bottom left
            rect.emplace_back(Point(transform.x, transform.y + transform.height * transform.scale));
            //bottom right
            rect.emplace_back(Point(transform.x + transform.width * transform.scale, transform.y + transform.height * transform.scale));

            return rect;
        }
        // 2. otherwise we find the coordinates of each vertex after the rotation
        //top right
        rect.emplace_back(Point(
                GetCenter(transform).x + ((transform.width * transform.scale / 2) * cos(Theta(transform.angle))) - ((transform.height * transform.scale / 2) * sin(Theta(transform.angle))),
                GetCenter(transform).y + ((transform.width * transform.scale / 2) * sin(Theta(transform.angle))) + ((transform.height * transform.scale / 2) * cos(Theta(transform.angle)))
        ));
        //top left
        rect.emplace_back(Point(
                GetCenter(transform).x - ((transform.width * transform.scale / 2) * cos(Theta(transform.angle))) - ((transform.height * transform.scale / 2) * sin(Theta(transform.angle))),
                GetCenter(transform).y - ((transform.width * transform.scale / 2) * sin(Theta(transform.angle))) + ((transform.height * transform.scale / 2) * cos(Theta(transform.angle)))
                ));
        //bottom left
        rect.emplace_back(Point(
                GetCenter(transform).x - ((transform.width * transform.scale / 2) * cos(Theta(transform.angle))) + ((transform.height * transform.scale / 2) * sin(Theta(transform.angle))),
                GetCenter(transform).y - ((transform.width * transform.scale / 2) * sin(Theta(transform.angle))) - ((transform.height * transform.scale / 2) * cos(Theta(transform.angle)))
                ));
        //bottom right
        rect.emplace_back(Point(
                GetCenter(transform).x + ((transform.width * transform.scale / 2) * cos(Theta(transform.angle))) + ((transform.height * transform.scale / 2) * sin(Theta(transform.angle))),
                GetCenter(transform).y + ((transform.width * transform.scale / 2) * sin(Theta(transform.angle))) - ((transform.height * transform.scale / 2) * cos(Theta(transform.angle)))
                ));

        return rect;
    }

    static bool HasVortexIntersection(const Rect &a, const Rect &b)
    {
        for(int rect_i = 0; rect_i < 2; ++rect_i)
        {
            const Rect& polygon = rect_i == 0 ? a : b;

            for(int i1 = 0; i1 < polygon.size(); ++i1)
            {
                const int i2 = (i1 + 1) % polygon.size();

                const double normalX = polygon[i2].y - polygon[i1].y;
                const double normalY = polygon[i2].x - polygon[i1].x;

                double minA = std::numeric_limits<double>::max();
                double maxA = std::numeric_limits<double>::min();
                for(auto ai : a) {
                    const double projected = normalX * ai.x + normalY * ai.y;
                    if( projected < minA ) minA = projected;
                    if( projected > maxA ) maxA = projected;
                }

                double minB = std::numeric_limits<double>::max();
                double maxB = std::numeric_limits<double>::min();
                for(auto bi : b) {
                    const double projected = normalX * bi.x + normalY * bi.y;
                    if( projected < minB ) minB = projected;
                    if( projected > maxB ) maxB = projected;
                }

                if( maxA < minB || maxB < minA )
                    return false;
            }
        }

        return true;
    }

};

#endif //CAR_EXAMPLE_COLLISION_H
