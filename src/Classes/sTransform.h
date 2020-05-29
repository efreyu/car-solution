#ifndef CAR_EXAMPLE_STRANSFORM_H
#define CAR_EXAMPLE_STRANSFORM_H

enum eDirection : std::size_t {
    UP, RIGHT, DOWN, LEFT
};

struct sTransform {
public:
    int x, y, width, height, scale;
    eDirection direction;

    sTransform() { x = y = width = height = 0; scale = 1; direction = eDirection::DOWN; }
    sTransform(int transformX, int transformY, int transformWidth, int transformHeight, eDirection transformDirection = eDirection::DOWN, int transformScale = 1)
            : x(transformX)
            , y(transformY)
            , width(transformWidth)
            , height(transformHeight)
            , direction(transformDirection)
            , scale(transformScale)
    {};
};

#endif //CAR_EXAMPLE_STRANSFORM_H
