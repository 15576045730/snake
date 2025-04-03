#ifndef ZIMO_HPP
#define ZIMO_HPP

#include "Color.hpp"
#include "Map.hpp"
extern unsigned char shuzi[10][8 * 2];

class Zimo
{
public:
    Zimo();                 
    ~Zimo();
    void draw();                

    //num = 数字几 w = 字的宽度 h = 字的高度 beginx beginy = 显示的坐标 bitmap = 你要显示哪一个字
    void zimoDisplay(int num, int w, int h, int beginx, int beginy, unsigned char *bitmap, Color color);
    
private:
    int _num;                       //数字
    int _z_w;                       //字的宽度
    int _z_h;                       //字的长度
    int _begin_x;                   //显示的X坐标
    int _begin_y;                   //显示的Y坐标
    unsigned char * _zimo;          
    Map* _map;
    Color _color;
};





#endif