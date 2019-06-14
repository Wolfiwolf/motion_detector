#pragma once
#include "Color.hpp"
#include "Vectors.hpp"

struct Pixel
{
    Vec2 pos;
    Color color;

    Pixel()
        : pos(0)
        , color(0)
    {

    }
    Pixel(int x, int y, const Color& color)
        : pos({x, y})
        , color(color)
    {

    }
};
