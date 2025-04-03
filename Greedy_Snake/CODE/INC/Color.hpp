#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
    Color(int r = 0, int g = 0, int b = 0, int a = 0);
    void setColor(int r, int g, int b);
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    int value() const;

private:
    int _red;
    int _green;
    int _blue;
    int _alpha;
};

#endif