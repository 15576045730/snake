#include "Touch.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <iostream>
using namespace std;

Touch::Touch()
{
    _Touch_fd = ::open("/dev/input/event0", O_RDWR);
    if (-1 == _Touch_fd)
    {
        throw std::runtime_error("open Touch event error");
    }
}

Touch::~Touch()
{
    ::close(_Touch_fd);
}

int Touch::get_touch(int * touch_x,int * touch_y)
{
    // 维护在一个结构体
    struct input_event ev;
    int ev_x0, ev_y0; // 起始坐标
    int ev_x, ev_y;   // 滑动的时候的实时坐标

    while (1)
    {
        int r = read(_Touch_fd, &ev, sizeof(ev));
        if (EV_ABS == ev.type)
        {
            if (ABS_X == ev.code) // x轴
            {
                ev_x = ev.value;
            }
            else if (ABS_Y == ev.code) // y轴
            {
                ev_y = ev.value;
            }
        }
        // 手碰到屏幕的时候为起始坐标
        // 详细解释就是：0x01 == ev.type 这是一个按键事件
        // BTN_TOUCH == ev.code 是否被触碰 触屏ev.code会等于330 也就是0x14a
        // 0x01 == ev.value 是否被激活 1代表被激活 0代表未被激活
        if (0x01 == ev.type && BTN_TOUCH == ev.code && 0x01 == ev.value)
        {
            ev_x0 = ev_x; // 把实时的横坐标定位初始横坐标
            ev_y0 = ev_y; // 把实时的纵坐标定位初始纵坐标
        }
        else if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x00 == ev.value)//手抬起来了
        {
            if(touch_x && touch_y)
            {
                *touch_x = ev_x * 800 / 1024;
                *touch_y = ev_y * 480 / 595;
                // *touch_x = ev_x;
                // *touch_y = ev_y;
            }
            // 检查滑动方向
            if (ev_x0 == ev_x && ev_y0 == ev_y)
            {
                return 5;
            }
            else // 滑动
            {    // 横坐标结束的位置肯定大于等于初始位置并且角度小于45度
                if (ev_x >= ev_x0 && (ev_x - ev_x0) >= abs(ev_y - ev_y0))
                {
                    // 如果横坐标结束的位置大于等于初始位置，并且变化的横坐标大于等于纵坐标的绝对值，则认为是向右滑动
                    return 4;
                }

                if (ev_x <= ev_x0 && abs(ev_x - ev_x0) >= abs(ev_y - ev_y0))
                {
                    // 如果横坐标结束的位置小于等于初始位置，并且变化的横坐标大于等于纵坐标的绝对值，则认为是向左滑动
                    return 3;
                }

                if (ev_y >= ev_y0 && abs(ev_y - ev_y0) > abs(ev_x - ev_x0))
                {
                    // 如果纵坐标结束的位置大于等于初始位置，并且变化的纵坐标大于横坐标的绝对值，则认为是向下滑动
                    return 2;
                }

                if (ev_y <= ev_y0 && abs(ev_y - ev_y0) > abs(ev_x - ev_x0))
                {
                    // 如果纵坐标结束的位置小于等于初始位置，并且变化的纵坐标大于横坐标的绝对值，则认为是向上滑动
                    return 1;
                }
            }
        }
    }
}
