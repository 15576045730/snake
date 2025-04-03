#include "Color.hpp"

Color::Color(int r, int g, int b, int a): _red(r), _green(g), _blue(b), _alpha(a) {}

void Color::setColor(int r, int g, int b)
{
    _red = r;
    _green = g;
    _blue = b;
}

void Color::setRed(int red)
{
    _red = red;
}

void Color::setGreen(int green)
{
    _green = green;
}

void Color::setBlue(int blue)
{
    _blue = blue;
}

int Color::value() const
{
    return (_red << 16 | _green << 8 | _blue);
}
