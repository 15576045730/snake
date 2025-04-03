#include "FoodTerm.hpp"
#include "Circle.hpp"
#include <cstdlib>
#include <ctime>

FoodTerm::FoodTerm(Map *map) : _map(map), _food_position(0, 0), _food_color(255, 0, 0)
{
}

FoodTerm::FoodTerm(Map *map, Point pos) : _map(map), _food_position(pos), _food_color(255, 0, 0)
{
}

FoodTerm::FoodTerm(Map *map, Point pos, Color color) : _map(map), _food_position(pos), _food_color(color)
{
}

void FoodTerm::generate()
{
    // 随机生成新的位置
    int row = rand() % _map->rows();
    int col = rand() % _map->cols();
    _food_position = _map->cell_position(row, col);

    // 随机生成颜色
    int r = rand() % 128;
    int g = rand() % 128;
    int b = rand() % 128;
    _food_color = Color(r, g, b);
}

void FoodTerm::draw()
{
    Circle(7.5, _food_position, _food_color).draw();
}

void FoodTerm::move(Point pos)
{
    this->_food_position = pos;
}

void FoodTerm::setColor(Color color)
{
    this->_food_color = color;
}

Point FoodTerm::pos() const
{
    return _food_position;
}
