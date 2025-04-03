#include "Game.hpp"
#include "Bitmap.hpp"
#include <iostream>
#include <thread>
#include "linux/input.h"
using namespace std;

Game::Game() : running(true)
{
    srand(static_cast<unsigned int>(time(nullptr))); // 初始化随机数种子
    _map = new Map;
    _snake = new Snake(_map);
    _touch = new Touch;
    this->generate_initial_food();
}

void Game::generate_initial_food()
{
    for (int i = 0; i < 5; ++i)
    { // 假设初始生成5个食物
        FoodTerm food(_map);
        bool validPosition = false;
        while (!validPosition)
        {
            food.generate(); // 根据您的实现来生成食物的位置和颜色等属性
            Point newPosition = food.pos();
            // 检查新位置是否与蛇身体重叠
            validPosition = true;
            for (const auto &pos : _snake->snake_body_position())
            {
                if (pos == newPosition)
                {
                    validPosition = false;
                    break;
                }
            }
        }
        _food.push_back(food);
    }
}

void Game::stop_touch()
{
    running.store(false);
}

void Game::generate_food()
{
    FoodTerm food(_map);
    bool validPosition = false;
    while (!validPosition)
    {
        food.generate();
        Point newPosition = food.pos();
        // 检查新位置是否与蛇身体重叠
        validPosition = true;
        for (const auto &pos : _snake->snake_body_position())
        {
            if (pos == newPosition)
            {
                validPosition = false;
                break;
            }
        }
    }
    _food.push_back(food);
}

Game::~Game()
{
    delete _snake;
    // delete _food;
    delete _map;
    delete _touch;
}

void Game::run()
{
    Bitmap bitmap("./mnt/kunkun/image/t.bmp");
    bitmap.draw();

    // 点击选择难度 0为普通模式 1为困难模式
    while (1)
    {
        int x0, y0;
        int key1 = _touch->get_touch(&x0, &y0);
        std::cout << x0 << ", " << y0 << std::endl;
        if (x0 >= 195 && x0 <= 325 && y0 >= 305 && y0 <= 353)
        {
            _snake->set_mode_switching(0);
            break;
        }
        else if (x0 >= 470 && x0 <= 600 && y0 >= 305 && y0 <= 340)
        {
            _snake->set_mode_switching(1);
            break;
        }
        else
        {
            std::cout << "点击失败，请选中位置点击" << std::endl;
        }
    }

    while (1)
    {
        // 速度 积分 以及横坐标具体位置
        int speed = 1;
        int points = 0;
        int hang = 705;

        // 绘制地图
        _map->draw();
        _map->draw_char(speed, points, hang);
        // 绘制贪吃蛇
        _snake->draw();
        // 生成食物并绘制
        for (auto &food : _food)
        {
            food.draw();
        }
        // 创建一个线程，用于处理触摸屏或按键
        running.store(true);
        std::thread(&Game::handle_touch, this).detach();

        // 游戏主循环
        while (1)
        {
            // 贪吃蛇移动
            _snake->move();

            // 根据模式切换变量进行不同的边界处理
            if (_snake->get_mode_switching() == 1)
            { // 困难模式：出界则游戏结束
                if (!_snake->check_border())
                {
                    break;
                }
            }
            else
            { // 无边界模式：调整蛇的位置
                _snake->no_border();
            }

            // 检查是否死亡（碰撞自身）
            if (_snake->die())
            {
                break;
            }

            // 是否吃到食物
            if (_snake->eat(_food))
            {
                ++speed;
                if (speed >= 8)
                {
                    speed = 8;
                }
                points += 10;
                _map->draw_char(speed, points, hang);
                // 重新生成食物并绘制
                // 如果食物数量少于5个，则生成新的食物
                if (_food.size() < 5)
                {
                    generate_food();
                    for (auto &f : _food)
                    {
                        f.draw();
                    }
                }
            }
            _snake->draw();
            // 延时
            std::this_thread::sleep_for(std::chrono::milliseconds(_snake->speed()));
        }

        Bitmap bmp2("./mnt/kunkun/image/j.bmp");
        bmp2.draw(150, 100);
        // 设置监听
        bool restart = false;
        while (!restart)
        {
            int x, y;
            _touch->get_touch(&x, &y);
            // 重新开始的位置为（200,300）到（265,300）
            if (x >= 200 && x <= 300 && y >= 265 && y <= 300)
            {
                restart = true;
            }
            // 退出游戏的位置为（405,505）到（265,300）
            else if (x >= 405 && x <= 505 && y >= 265 && y <= 300)
            {
                return;
            }
        }
        // 重置游戏
        reset_game();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Game::reset_game()
{
    stop_touch(); // 停止旧的触摸事件处理线程
    delete _snake;
    _snake = new Snake(_map);
    _food.clear();
    generate_initial_food();
}

void Game::handle_touch()
{
    while (running.load())
    {
        int x, y;
        int key = _touch->get_touch(&x, &y);
        if (key == 1)
        {
            _snake->set_direction(Direction::Up);
        }
        else if (key == 2)
        {
            _snake->set_direction(Direction::Down);
        }
        else if (key == 3)
        {
            _snake->set_direction(Direction::Left);
        }
        else if (key == 4)
        {
            _snake->set_direction(Direction::Right);
        }
        else if (key == 5)
        {
            if (x > 700 && x < 740 && y > 300 && y < 335)
            {
                _snake->set_direction(Direction::Up);
            }
            else if (x > 700 && x < 740 && y > 395 && y < 425)
            {
                _snake->set_direction(Direction::Down);
            }
            else if (x > 665 && x < 695 && y > 345 && y < 380)
            {
                _snake->set_direction(Direction::Left);
            }
            else if (x > 745 && x < 800 && y > 345 && y < 380)
            {
                _snake->set_direction(Direction::Right);
            }
        }
    }
}
