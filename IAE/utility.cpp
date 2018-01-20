#include "utility.h"
// Определяет является ли найденый путь ссылкой на родительский каталог
// или ссылкой каталога на самого себя
namespace IAE{
namespace utility{
bool isDotOrDotdot(char* path)
{
	if((strcmp(".", path) == 0) || (strcmp("..", path) == 0))
		return true;
	else return false;
}

strings_t getPathes(std::string path)
{
    std::vector<std::string> res;
    std::string buf;
    luint pos = 0;
    while(pos < path.size())
    {
        buf.push_back(path[pos]);
        if(path[pos] == '\\' || path[pos] == '/')
        {
            res.push_back(buf);
        }
        pos++;
    }
    if(!buf.empty()) res.push_back(buf);
    return res;
}

strings_t getPathElements(std::string path)
{
    std::vector<std::string> res;
    std::string buf;
    luint pos = 0;
    while(pos < path.size())
    {
        if(path[pos] == '\\' || path[pos] == '/')
        {
            res.push_back(buf);
        }
        buf.push_back(path[pos]);
        pos++;
    }
    return res;
}

std::string sliceString(std::string& st, uint begin, uint end)
{
    if(end < begin) throw std::out_of_range("Invalid range");
    return st.substr(begin, end-begin);
}

}// end namespace utility
}// end namespace IAE
