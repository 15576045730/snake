#include "Screen.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <iostream>
#include <cerrno>
#include <cstdio>

Screen::Screen(const char *name):_name(name)
{
    _fd = ::open(name, O_RDWR);
    if (-1 == _fd)
    {
        std::perror("open lcd error");
        exit(1); // 进程退出
    }
    //2 将屏幕映射
    _addr =  (int*)::mmap(NULL,
            800 * 480 * 4,
            PROT_READ | PROT_WRITE,//权限
            MAP_SHARED,//映射标志
            _fd,
            0);

    if(MAP_FAILED == _addr)
    {
        std::perror("mmap lcd error");
        exit(1);
    }
}

// Screen::Screen(const Screen &rhs)
// {
//     _fd = ::open(rhs._name, O_RDWR);
//     if (-1 == _fd)
//     {
//         std::perror("open lcd error");
//         exit(1); // 进程退出
//     }
//     //2 将屏幕映射
//     _addr =  (int*)::mmap(NULL,
//             800 * 480 * 4,
//             PROT_READ | PROT_WRITE,//权限
//             MAP_SHARED,//映射标志
//             _fd,
//             0);

//     if(MAP_FAILED == _addr)
//     {
//         std::perror("mmap lcd error");
//         exit(1);
//     }
// }

void Screen::draw_point(int x, int y, int color)
{
    if(x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        //画点
        *(_addr + y * 800 + x) = color;
    }
} 
void Screen::draw_point(Point pos, Color color)
{
    draw_point(pos.getX(), pos.getY(), color.value());
}


void Screen::set_background(Color color)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            this->draw_point(j,i,color.value());
        }
        
    }
    
}

Screen::~Screen()
{
    ::close(_fd);
    ::munmap(_addr, 800 * 480 * 4);
}

