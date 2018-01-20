// Этот файл предназначен для доступа к инструментам и возможностям ОС.
#ifndef iae_SYS
#define iae_SYS
#include "iaetypes.h"
#include "utility.h"

namespace IAE
{
    namespace sys
    {
        #ifdef WIN32 // Windows section
            #include "windows.h"
            #define iaeFileID HANDLE
            #define invalidFile INVALID_HANDLE_VALUE
            #define ERROR_EXIST ERROR_ALREADY_EXISTS
            #define ERROR_PATH ERROR_PATH_NOT_FOUND
        #else // other platform
            typedef int    iaeFileID;
            #define invalidFile -1 // WARNING: should check this value
        #endif
        // Режимы открытия файлов
        enum fileMode{read = 1, write = 2, readWrite = 3, append = 4};
        // Режимы смещения файлового указателя
        enum shiftMode{begin = 1, current = 3, end = 7};

        iaeFileID getFileID(char* path, fileMode mode);
        int fwrite(iaeFileID id, void* buff, int size);
        int fread(iaeFileID id, void* buff, int size);
        int setFilePos(iaeFileID id, int pos, shiftMode mode);
        int getFilePos(iaeFileID id);
        bool closeFileID(iaeFileID id);
        int createDir(char* path);
        int buildDirs(char* path);

        #ifdef WIN32 // Конекретная реализация функций для платформ
            #include "iae_SYS_WINDOWS_.cpp"
        #else
            #include "iae_SYS_POSIX.cpp"
        #endif
    }
}
#endif
