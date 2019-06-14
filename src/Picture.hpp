#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "vendor/stb_image/stb_image.hpp"
#include "Pixel.hpp"
#include "Object.hpp"

class Picture
{
private:
    int m_width;
    int m_height;
    int m_channels;

    unsigned char* m_buffer;

    std::vector<Pixel*> m_pixels;

    static Pixel* s_error_pixel;

    std::vector<Object*> m_objects;

public:
    Picture(const std::string& filepath);
    ~Picture();

    void group_zones();

    //GET
    inline int get_width() const
    {
        return m_width;
    }

    inline int get_height() const
    {
        return m_height;
    }

    Pixel* get_pixel(int x, int y);

    inline const std::vector<Object*>& get_objects() const
    {
        return m_objects;
    }

private:

};
