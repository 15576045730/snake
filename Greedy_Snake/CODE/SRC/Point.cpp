#include "Point.hpp"

Point::Point() : _X(0), _Y(0) {}

Point::Point(int x, int y) : _X(x), _Y(y) {}

int Point::getX()
{
    return _X;
}

void Point::setX(int x)
{
    _X = x;
}

int Point::getY()
{
    return _Y;
}

void Point::setY(int y)
{
    _Y = y;
}

void Point::move(int x, int y)
{
    _X = x;
    _Y = y;
}

bool Point::operator==(const Point &rhs) const
{
     return (this->_X == rhs._X && this->_Y == rhs._Y);
}