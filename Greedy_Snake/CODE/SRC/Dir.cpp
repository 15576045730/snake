#include "Dir.hpp"
#include <stdexcept>

Dir::Dir(std::string path) : _path(path)
{
    _pdir = ::opendir(path.c_str());
    if (nullptr == _pdir)
    {
        throw std::runtime_error("open dir error");
    }
}

Dir::~Dir()
{
    ::closedir(_pdir);
}

List Dir::getAllFilenames() const
{
    List list;
    struct dirent *dirt;
    while (1)
    {
        dirt = readdir(_pdir);
        if (nullptr == dirt)
        {
            break;
        }
        std::string pathfile = _path;
        if ('/' != pathfile.back())
        {
            pathfile += "/";
        }
        pathfile += dirt->d_name;
        list.push_back(pathfile);
    }

    return list;
}

List Dir::getBitmapNames() const
{
    List list;
    struct dirent *dirt;
    while (1)
    {
        dirt = readdir(_pdir);
        if (nullptr == dirt)
        {
            break;
        }
        if (std::string(dirt->d_name) == "." || std::string(dirt->d_name) == "..") {
            continue;
        }
        std::string pathfile = _path;
        if ('/' != pathfile.back())
        {
            pathfile += "/";
        }
        pathfile += dirt->d_name;
        list.push_back(pathfile);
    }
    return list;
}
