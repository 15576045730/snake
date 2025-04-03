#include "Snake.hpp"
#include "Bitmap.hpp"
#include <iostream>

Snake::Snake(Map *map) : _map(map), _direct(Direction::Right), _speed(800), _mode_switching(0)
{
    _snake.emplace_front(_map->cell_size(), _map->cell_size(), _map->cell_position(3, 5), Color(255, 0, 0));
    _snake.emplace_back(_map->cell_size(), _map->cell_size(), _map->cell_position(3, 4), Color(0, 0, 255));
    _snake.emplace_back(_map->cell_size(), _map->cell_size(), _map->cell_position(3, 3), Color(0, 0, 255));
}

void Snake::draw()
{
    for (int i = 0; i < _snake.size(); i++)
    {
        _snake.at(i).draw();
    }
}

// 移动
int Snake::move()
{
    // 记录尾巴
    Point tail_pos = _snake.back().pos();
    // 移动身体
    for (int i = _snake.size() - 1; i > 0; i--)
    {
        _snake[i].move(_snake[i - 1].pos().getX(), _snake[i - 1].pos().getY()); // 最后一个移动到倒数第二个
    }

    // 移动头部
    int step = _map->cell_size() + _map->gap_size(); // 16 计算步长

    if (_direct == Direction::Up)
    {
        _snake[0].move(_snake[0].pos().getX(), _snake[0].pos().getY() - step); // 移动头部
    }
    else if (_direct == Direction::Down)
    {
        _snake[0].move(_snake[0].pos().getX(), _snake[0].pos().getY() + step); // 移动头部
    }
    else if (_direct == Direction::Left)
    {
        _snake[0].move(_snake[0].pos().getX() - step, _snake[0].pos().getY()); // 移动头部
    }
    else if (_direct == Direction::Right)
    {
        _snake[0].move(_snake[0].pos().getX() + step, _snake[0].pos().getY()); // 移动头部
    }

    
    // 擦除原来尾巴颜色
    Rect(_map->cell_size(), _map->cell_size(), tail_pos, _map->cell_color()).draw();

    return 1;
}

std::vector<Point> Snake::snake_body_position() const
{
    std::vector<Point> position;
    for (const auto &sep : _snake)
    {
        position.push_back(sep.pos());
    }

    return std::vector<Point>();
}

bool Snake::eat(std::vector<FoodTerm> &food)
{
    for (auto it = food.begin(); it != food.end();)
    {
        if (_snake.front().pos() == it->pos())
        {
            _snake.emplace_back(_map->cell_size(), _map->cell_size(), it->pos(), Color(0, 0, 255));
            if (_speed > 100)
                _speed -= 100;
            std::cout << speed() << std::endl;
            // 移除已经被吃掉的食物
            it = food.erase(it);
            return true;
        }
        else
        {
            ++it;
        }
    }
    return false;
}

bool Snake::check_border()
{
    Point p = _snake.front().pos();
    int x = p.getX();
    int y = p.getY();

    // 检查是否超出上边界
    if (y < 0)
    {
        return false;
    }
    // 检查是否超出下边界
    else if (y >= _map->cell_size() * _map->rows() + (_map->rows() - 1) * _map->gap_size())
    {
        return false;
    }
    // 检查是否超出左边界
    else if (x < 0)
    {
        return false;
    }
    // 检查是否超出右边界
    else if (x >= _map->cell_size() * _map->cols() + (_map->cols() - 1) * _map->gap_size())
    {
        return false;
    }

    // 如果没有越界，则返回 true
    return true;
}

void Snake::no_border()
{
    Point p = _snake.front().pos();
    int x = p.getX();
    int y = p.getY();
    int map_width = _map->cell_size() * _map->cols() + (_map->cols() - 1) * _map->gap_size();
    int map_height = _map->cell_size() * _map->rows() + (_map->rows() - 1) * _map->gap_size();

    if (x < 0)
    {
        x = map_width - _map->cell_size();
    }
    else if (x >= map_width)
    {
        x = 0;
    }

    if (y < 0)
    {
        y = map_height - _map->cell_size();
    }
    else if (y >= map_height)
    {
        y = 0;
    }

    // 更新蛇头位置
    _snake.front().move(x, y);
}

bool Snake::die()
{
    // 记录蛇头
    Point head_pos = _snake.front().pos();
    // 判断蛇头移动的方向有没有和身体重叠 如果重叠就会死亡
    for (int i = 1; i < _snake.size(); i++)
    {
        if (head_pos == _snake.at(i).pos())
        {
            return true;
        }
    }
    return false;
}

void Snake::set_direction(Direction d)
{
    // 禁止掉头：不允许直接将方向设置为当前方向的反方向
    if ((_direct == Direction::Up && d == Direction::Down) || (_direct == Direction::Down && d == Direction::Up) || (_direct == Direction::Left && d == Direction::Right) || (_direct == Direction::Right && d == Direction::Left))
    {
        return;
    }
    this->_direct = d;
}

int Snake::speed() const
{
    return this->_speed;
}

int Snake::get_mode_switching()
{
    return _mode_switching;
}

void Snake::set_mode_switching(int mode_switching)
{
    this->_mode_switching = mode_switching;
}
