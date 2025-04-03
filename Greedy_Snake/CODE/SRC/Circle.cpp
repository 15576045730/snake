#include "Circle.hpp"

double Circle::pi = 3.14;

Circle::Circle(double r) : _r(r), _pos(0,0), _color(255, 255, 255)
{
}

Circle::Circle(double r, Point pos) : _r(r), _pos(pos), _color(255, 255, 255)
{
}

Circle::Circle(double r, Point pos, Color color) : _r(r), _pos(pos), _color(color)
{
}

int Circle::getR() const
{
    return this->_r;
}


void Circle::move(Point pos)
{
    this->_pos = pos;
}

//自己写的太low了 学bresenham算法去
// void Circle::draw()
// {
//     int radius = getR();
//     // 计算圆心坐标，_pos 是圆的左上角位置
//     int center_x = _pos.getX() + radius; 
//     int center_y = _pos.getY() + radius; 

//     for (int y = -radius; y <= radius; ++y) {
//         for (int x = -radius; x <= radius; ++x) {
//             // 检查点是否在圆内
//             if (x * x + y * y <= radius * radius) {
//                 // 在屏幕上绘制该点
//                 Screen::getInstance().draw_point(Point(center_x + x, center_y + y), _color);
//             }
//         }
//     }
// }
//学了后
void Circle::draw()
{
    int radius = getR();
    // 计算圆心坐标，_pos 是圆的左上角位置
    int center_x = _pos.getX() + radius; 
    int center_y = _pos.getY() + radius; 
    int x = 0;
    int y = radius;
    //误差值公式为 d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - r * r
    int d =  1 - 2 * radius;
    while (y >= x) {
        // 绘制当前点和对称点，并填充垂直线段
        for (int i = center_y - y; i <= center_y + y; ++i) {
            Screen::getInstance().draw_point(Point(center_x + x, i), _color);
            Screen::getInstance().draw_point(Point(center_x - x, i), _color);
        }
        for (int i = center_y - x; i <= center_y + x; ++i) {
            Screen::getInstance().draw_point(Point(center_x + y, i), _color);
            Screen::getInstance().draw_point(Point(center_x - y, i), _color);
        }

        ++x;
        if (d > 0) {
            --y;
            d += 2 * (x - y) + 1;
        } else {
            d += 2 * x + 1;
        }
    }

}

Point Circle::pos() const
{
    return this->_pos;
}

void Circle::setColor(Color color)
{
    this->_color = color;
}

