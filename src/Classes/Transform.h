/* Created by efreyu on 26.05.2020. */
#pragma once

enum eDirection : std::size_t {
    UP, RIGHT, DOWN, LEFT
};

struct sTransform {
public:
    int x, y, width, height;
    eDirection direction;

    sTransform() { x = y = width = height = 0; direction = eDirection::DOWN; }
    sTransform(int transformX, int transformY, int transformWidth, int transformHeight, eDirection transformDirection = eDirection::DOWN)
            : x(transformX)
            , y(transformY)
            , width(transformWidth)
            , height(transformHeight)
            , direction(transformDirection)
    {};
};