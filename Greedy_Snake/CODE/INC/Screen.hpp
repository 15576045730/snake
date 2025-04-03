#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Point.hpp"
#include "Color.hpp"

class Screen
{
public:
    // 获取唯一的实例
    static Screen &getInstance()
    {
        static Screen instance("/dev/fb0"); // 静态局部变量，线程安全
        return instance;
    }

    // 绘制点的方法
    void draw_point(int x, int y, int color);
    void draw_point(Point pos, Color color);
    void set_background(Color color);

    // 析构函数
    ~Screen();

private:
    // 私有构造函数
    explicit Screen(const char *name);
    // 禁止拷贝构造和赋值操作符
    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;

    const char *_name; // 屏幕文件名称
    int _fd;           // 屏幕文件描述符
    int *_addr;        // 映射后的首地址
};

#endif // SCREEN_HPP