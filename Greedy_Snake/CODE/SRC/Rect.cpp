#include "Rect.hpp"

Rect::Rect(int w, int h) : _w(w), _h(h), _pos(0, 0), _color(255, 255, 255)
{
}

Rect::Rect(int w, int h, Point pos) : _w(w), _h(h), _pos(pos), _color(255, 255, 255)
{
}

Rect::Rect(int w, int h, Point pos, Color color) : _w(w), _h(h), _pos(pos), _color(color)
{
}

void Rect::draw()
{
    // 获取 Screen 的唯一实例
    // Screen& screen = Screen::getInstance();

    for (int i = _pos.getY(); i < _h + _pos.getY(); i++)
    {
        for (int j = _pos.getX(); j < _w + _pos.getX(); j++)
        {
            Screen::getInstance().draw_point(Point(j, i), _color);
        }
    }
}

void Rect::move(int x, int y)
{
    this->_pos.move(x, y);
}

void Rect::move(Point pos)
{
    this->_pos = pos;
}

void Rect::resize(int w, int h)
{
    this->_w = w;
    this->_h = h;
}

void Rect::setColor(Color color)
{
    this->_color = color;
}

Point Rect::pos() const
{
    return this->_pos;
}
