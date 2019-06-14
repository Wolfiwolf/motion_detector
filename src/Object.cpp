#include "Object.hpp"

Object::Object()
    : m_position(0)
    , m_color(0)
{

}

Object::Object(int x, int y)
    : m_position({x, y})
    , m_color(0)
{

}

Object::~Object()
{

}

void Object::add_pixel(Pixel* pixel)
{
    calculate_color(pixel->color);
    m_pixels.push_back(pixel);
}

void Object::calculate_pos()
{
    int sum_x = 0;
    int sum_y = 0;

    for(Pixel* pixel : m_pixels)
    {
        sum_x += pixel->pos.x;
        sum_y += pixel->pos.y;
    }

    m_position.x = sum_x / m_pixels.size();
    m_position.y = sum_y / m_pixels.size();

}

//PRIVATE

void Object::calculate_color(const Color& new_color)
{
    int temp = m_color.r * m_pixels.size();
    temp += new_color.r;
    m_color.r = temp / (m_pixels.size() + 1);

    temp = m_color.g * m_pixels.size();
    temp += new_color.g;
    m_color.g = temp / (m_pixels.size() + 1);

    temp = m_color.b * m_pixels.size();
    temp += new_color.b;
    m_color.b = temp / (m_pixels.size() + 1);

}




//--------------END---------

std::ostream& operator<<(std::ostream& stream, const Object& object)
{
    stream << "Color => " << object.get_color().r << " " << object.get_color().g << " " << object.get_color().b << "\n";
    stream << "Position => " << object.get_pos().x << " " << object.get_pos().y << "\n";


    return stream;
}
