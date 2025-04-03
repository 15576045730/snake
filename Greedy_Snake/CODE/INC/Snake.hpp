#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include <vector>
#include "Rect.hpp"
#include "Map.hpp"
#include "Circle.hpp"
#include "Point.hpp"
#include "FoodTerm.hpp"

enum Direction
{
    Error,
    Up,
    Down,
    Left,
    Right
};

class Snake
{
public:
    Snake(Map* map);
    void draw();
    int move();
    std::vector<Point> snake_body_position() const;     //蛇的身体位置 
    bool eat(std::vector<FoodTerm> &food);              //吃食物
    bool check_border();                                //边界检查 困难版 碰到就死
    void no_border();                                   //无边界   简单版 对面出来
    bool die();
    void set_direction(Direction d);
    int speed() const;
    int get_mode_switching();
    void set_mode_switching(int mode_switching); 


private:
    std::deque<Rect> _snake;        //deque容器
    std::deque<Circle> _snakeC;     //deque容器
    Map* _map;                      //地图对象
    Direction _direct;              //枚举类型记录方向
    int _speed;                     //速度
    int _mode_switching;             //模式切换
};






#endif