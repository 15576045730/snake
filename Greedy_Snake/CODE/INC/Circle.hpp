#ifndef ROUND_HPP
#define ROUND_HPP

#include "Point.hpp"
#include "Color.hpp"
#include "Screen.hpp"

class Circle
{
public:
    Circle() = default;
    Circle(double r);
    Circle(double r, Point pos);
    Circle(double r, Point pos, Color color);
    int getR() const;
    void move(Point pos);
    void setColor(Color color);

    void draw();

    Point pos() const;
private:
    static double pi;

    double _r;
    Color _color;
    Point _pos;     
};

#endif