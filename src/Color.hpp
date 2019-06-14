#pragma once

struct Color
{
    int r;
    int g;
    int b;

    Color()
        : r(0)
        , g(0)
        , b(0)
    {

    }

    Color(unsigned int rgb)
        : r(rgb)
        , g(rgb)
        , b(rgb)
    {

    }

    Color(unsigned int r, unsigned int g, unsigned int b)
        : r(r)
        , g(g)
        , b(b)
    {

    }
};
