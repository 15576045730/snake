#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <string>
#include "Screen.hpp"
#include "Color.hpp"

using uchar = unsigned char;

class Bitmap
{
public:
    Bitmap(std::string filename);
    ~Bitmap();
    void draw(int x=0, int y=0);
private:
    int _fd;                    //打开路径地址的文件描述符
    int _size;                  //文件大小
    int _width, _height;        //宽度 高度
    short _bpp;                 //bits per pixel"每像素位数
    uchar* _pixs;               //表示图像的像素数据
};

#endif