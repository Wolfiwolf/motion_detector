#pragma once

#include <vector>
#include <iostream>

#include "Pixel.hpp"


class Object
{
private:
    Vec2 m_position;

    Color m_color;

    std::vector<Pixel*> m_pixels;


public:
    Object();
    Object(int x, int y);
    ~Object();

    void add_pixel(Pixel* pixel);

    void calculate_pos();

    //GET & SET

    inline const Color& get_color() const
    {
        return m_color;
    }

    inline const Vec2& get_pos() const
    {
        return m_position;
    }

    inline int get_weight() const
    {
        return m_pixels.size();
    }


private:
    void calculate_color(const Color& new_color);


};


std::ostream& operator<<(std::ostream& stream, const Object& object);
