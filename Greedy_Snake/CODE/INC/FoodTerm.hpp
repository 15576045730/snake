#ifndef FOODTERM_HPP
#define FOODTERM_HPP

#include "Map.hpp"
#include "Color.hpp"
#include "Point.hpp"

class FoodTerm {
public:
    // 构造函数
    FoodTerm(Map* map); // 仅需要Map指针的构造函数
    FoodTerm(Map* map, Point pos);
    FoodTerm(Map* map, Point pos, Color color);

    void generate();            // 食物生成的方法
    void draw();                // 绘制食物的方法
    void move(Point pos);
    void setColor(Color color);
    Point pos() const;

private:
    Map* _map;                  //地图对象
    Color _food_color;          //食物颜色
    Point _food_position;       //食物位置
};

#endif