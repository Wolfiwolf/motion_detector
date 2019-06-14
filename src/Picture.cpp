#include "Picture.hpp"

#include <cmath>

Pixel* Picture::s_error_pixel = NULL;

Picture::Picture(const std::string& filepath)
{
    m_buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channels, STBI_rgb);

    m_pixels.reserve(m_width * m_height);

    for(int i = 0; i < m_height; i++)
    {
        for(int p = 0; p < m_width * 3;)
        {
            Pixel* pixel = new Pixel;

            pixel->pos.x = p / 3;
            pixel->pos.y = i;

            pixel->color.r = (int)m_buffer[p + (i * m_width * 3)];
            p++;
            pixel->color.g = (int)m_buffer[p + (i * m_width * 3)];
            p++;
            pixel->color.b = (int)m_buffer[p + (i * m_width * 3)];
            p++;

            m_pixels.push_back(pixel);
        }
    }

}

Picture::~Picture()
{
    for(Pixel* pixel : m_pixels)
    {
        delete pixel;
    }

    stbi_image_free(m_buffer);
}


//PUBLIC

void Picture::group_zones()
{
    int object_index = -1;

    m_objects.reserve(1000);

    for(int i = 50; i < m_pixels.size(); i++)
    {
        if(i % 50 == 0)
        {
            m_objects.push_back(new Object(m_pixels[i - 50]->pos.x, m_pixels[i - 50]->pos.y));
            object_index++;
        }

        m_objects[object_index]->add_pixel(m_pixels[i - 50]);

    }

}

Pixel* Picture::get_pixel(int x, int y)
{
    return m_pixels[(y * m_width) + x];
}
