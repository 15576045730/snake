#ifndef MAP_HPP
#define MAP_HPP

#include "Color.hpp"
#include "Rect.hpp"

//地图类的声明
class Map
{
public:
    Map();
    ~Map();
    void draw();                        //绘制
    int cell_size() const;              //获取单元格大小
    int gap_size() const;               //获取间距大小
    Point cell_position(int r, int c) const; //获取指定行列的单元格的坐标
    Color cell_color() const;           //获取数组颜色
    void draw_char(int speed, int points, int hang);                   //控制右边空间数据绘制
    
    int rows() const;                   //获取行数
    int cols() const;                   //获取列数
private:
    int _rows;                          //行数
    int _cols;                          //列数
    int _cell_size;                     //单元格大小
    int _gap_size;                      //间距大小
    Color _cell_color;                  //单元格颜色
    Rect* _cells;                       //矩形数组
};







#endif