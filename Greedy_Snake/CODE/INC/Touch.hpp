#ifndef TOUCH_HPP
#define TOUCH_HPP

#include "Snake.hpp"

class Touch
{
public:
    Touch();
    ~Touch();
    int get_touch(int * touch_x,int * touch_y);
    
private:
    int _Touch_fd;          //触摸板的文件描述符
};





#endif