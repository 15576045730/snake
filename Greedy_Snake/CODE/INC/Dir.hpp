#ifndef DIR_HPP
#define DIR_HPP

#include <string>
#include <dirent.h>
#include "List.hpp"

class Dir
{
public:
    Dir(std::string path);
    ~Dir();
    List getAllFilenames() const;
    List getBitmapNames() const;

private:
    DIR *_pdir;                         //opendir()打开的目录流 拿这个接收
    std::string _path;                  //目录路径字符串
};

#endif