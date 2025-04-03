#ifndef RECT_HPP
#define RECT_HPP

#include "Point.hpp"
#include "Color.hpp"
#include "Screen.hpp"

class Rect
{
public:
    Rect() = default;
    Rect(int w, int h);
    Rect(int w, int h, Point pos);
    Rect(int w, int h, Point pos, Color color);
    void draw();
    void move(int x, int y);
    void move(Point pos);
    void resize(int w, int h);
    void setColor(Color color);

    Point pos() const;
    
private:
    int _w;                 //矩形的宽度
    int _h;                 //矩形的高度
    Point _pos;             //点的对象
    Color _color;           //颜色的对象
};

#endif