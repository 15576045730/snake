#include "Map.hpp"
#include "Bitmap.hpp"
#include "Zimo.hpp"
#include <iostream>
#include <vector>

Map::Map() : _rows(30), _cols(40), _cell_size(15), _gap_size(1), _cell_color(Color(200, 200, 200))
{
    _cells = new Rect[_rows * _cols];
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            _cells[i * _cols + j].resize(_cell_size, _cell_size);
            _cells[i * _cols + j].setColor(_cell_color);
            _cells[i * _cols + j].move(j * (_cell_size + _gap_size), i * (_cell_size + _gap_size));
        }
    }
}

Map::~Map()
{
    delete[] _cells;
}

void Map::draw()
{
    // 设置背景颜色
    Screen::getInstance().set_background(Color(255, 255, 255));

    // 绘制单元格
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            _cells[i * _cols + j].draw();
        }
    }

    // 绘制右侧小图片
    Bitmap bmp("./mnt/kunkun/image/h.bmp");
    bmp.draw(640, 0);
}

int Map::cell_size() const
{
    return this->_cell_size;
}

int Map::gap_size() const
{
    return this->_gap_size;
}

Point Map::cell_position(int r, int c) const
{
    return _cells[r * _cols + c].pos();
}

Color Map::cell_color() const
{
    return this->_cell_color;
}

void Map::draw_char(int speed, int points, int hang)
{
    Zimo zimo;
    zimo.zimoDisplay(speed, 8, 16, 714, 65, shuzi[speed], 0x000000);

    // 显示分数，从最低位开始
    int x = hang; // 假设这是x坐标

    if (points == 0) 
    {
        // 如果分数为0，直接显示一个0
        zimo.zimoDisplay(0, 8, 16, x, 128, shuzi[0], 0x000000);
    } 
    else 
    {
        // 对于非零分数，我们分解数字，从最左边开始显示
        std::vector<int> F;
        while (points > 0) 
        {
            F.push_back(points % 10);
            points /= 10;
        }
        int offset = F.size() * 20 - 20; // 计算起始偏移量，确保数字从左到右显示
        for (size_t i = 0; i < F.size(); ++i) 
        {
            zimo.zimoDisplay(F[i], 8, 16, x + offset, 128, shuzi[F[i]], 0x000000);
            offset -= 20; // 每次递减，因为是从左到右显示
        }
    }
}

int Map::rows() const
{
    return this->_rows;
}

int Map::cols() const
{
    return this->_cols;
}
