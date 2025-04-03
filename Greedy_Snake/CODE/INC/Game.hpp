#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <atomic>
#include "Map.hpp"
#include "Snake.hpp"
#include "Touch.hpp"
#include "FoodTerm.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();
    void reset_game();              //重置游戏
    void handle_touch();            //手柄控制
    void generate_food();           //添加一个食物
    void generate_initial_food();   // 初始化多个食物项
    void stop_touch();              //停止触摸板线程
private:
    std::atomic<bool> running;      // 用于指示线程是否应该继续运行
    Map* _map;                      //地图的对象
    Snake* _snake;                  //蛇的对象
    std::vector<FoodTerm> _food;    // 将_food更改为std::vector<FoodTerm>
    // Food* _food;                 //食物的对象
    Touch* _touch;                  //触摸屏的对象
};






#endif