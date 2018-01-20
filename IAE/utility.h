// Файл предоставляет вспомогательные функции для работы со всем чем можно
// Суда попадают функции которые не вошли в другие разделы
#ifndef UTILITY
#define UTILITY
#include "iaetypes.h"
#include <string.h> // Обработка строк
#include <stdexcept>

namespace IAE
{
    namespace utility
    {
        bool isDotOrDotdot(char* path);
        strings_t getPathes(std::string path);
        strings_t getPathElements(std::string path);
        std::string sliceString(std::string& st, uint begin, uint end);
    }
}
#endif
