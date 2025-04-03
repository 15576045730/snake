#include "Bitmap.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

Bitmap::Bitmap(std::string filename)
{
    //1 打开文件
    int _fd = ::open(filename.c_str(), O_RDONLY);
    if (-1 == _fd)
    {
        throw std::runtime_error("open bmp error!");
    }
    //这里要马上进行bmp文件的判断  看是不是真的bmp文件  这里要自己想办法搞定
    char bm[2] = {0};
    read(_fd, bm, 2);                                //这里是因为 read(_fd, bm, 2);前两个字节表示标准文件头
    if (bm[0] != 'B' || bm[1] != 'M')
    {
        throw std::logic_error("这不是bmp图片");
    }
    //2 读写这个文件
    //获取三个信息   宽  高 色深
    read(_fd, &_size, 4);                             //这里是指第三个字节到第六个字节表示bmp大小
    lseek(_fd, 0x12, SEEK_SET);                       //这里是将光标挪到第十八个字节位置
    read(_fd, &_width, 4);                            //这里是读取第十九到第二十二个字节 也就是宽度大小
    read(_fd, &_height, 4);                           //这里是读取第二十三到第二十六个字节 也就是高度大小  也不一定 是大概
    lseek(_fd, 0x1c, SEEK_SET);             
    read(_fd, &_bpp, 2);
    std::cout << _size << "," << _width << " " << _height << std::endl;

    _pixs = new uchar[_size - 54];
    lseek(_fd, 0x36, SEEK_SET);
    read(_fd, _pixs, _size - 54);
}

Bitmap::~Bitmap()
{
    ::close(_fd);
    delete[] _pixs;
}

void Bitmap::draw(int x, int y)
{
    uchar r, g, b;
    uchar *p = _pixs;

    int n = (4 - _width * _bpp / 8 % 4) % 4;

    for (int i = _height - 1; i >= 0; i--)
    {
        for (int j = 0; j < _width; j++)
        {
            r = *p++;
            g = *p++;
            b = *p++;
            Screen::getInstance().draw_point(j+x, i+y, Color(r, g, b).value());
        }
        p += n;
    }
}
