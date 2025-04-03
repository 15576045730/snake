#ifndef POINT_HPP
#define POINT_HPP


class Point
{
public:
    Point();
    Point(int x, int y);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    void move(int x, int y);

    bool operator==(const Point& rhs) const;
private:
    int _X;             //点的横坐标
    int _Y;             //点的纵坐标
};



#endif
