#ifndef IAESYSWIN
#define IAESYSWIN
iaeFileID getFileID(char* path, fileMode mode)
{
    DWORD winModeFile;
    DWORD shareFileMode;
    DWORD operation;
    switch(mode) // Выбор режима открытия файла
    {
        case read:
            winModeFile = GENERIC_READ;
            shareFileMode = FILE_SHARE_READ;
            operation = OPEN_EXISTING;
            break;
        case write:
            winModeFile = GENERIC_WRITE;
            shareFileMode = FILE_SHARE_WRITE;
            operation = OPEN_ALWAYS;
            break;
        case readWrite:
            winModeFile = GENERIC_WRITE | GENERIC_READ;
            shareFileMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
            operation = OPEN_ALWAYS;
            break;
        case append:
            winModeFile = GENERIC_WRITE;
            shareFileMode = FILE_SHARE_WRITE;
            operation = OPEN_EXISTING;
            break;
        default:
            return invalidFile;
    }

    return CreateFile(path, winModeFile, shareFileMode, NULL, operation, FILE_ATTRIBUTE_NORMAL, NULL);
}

int fwrite(iaeFileID id, void* buff, int size)
{
    luint countWriteBytes = 0;
    WriteFile(id, buff, size, &countWriteBytes, NULL);
    return countWriteBytes;
}

int fread(iaeFileID id, void* buff, int size)
{
    luint countReadBytes = 0;
    ReadFile(id, buff, size, &countReadBytes, NULL);
    return countReadBytes;
}

int setFilePos(iaeFileID id, int pos, shiftMode mode)
{
    DWORD method;
    switch (mode)
    {
        case begin:
            method = FILE_BEGIN;
            break;
        case current:
            method = FILE_CURRENT;
            break;
        case end:
            method = FILE_END;
            break;
        default:
            return -1;
    }

    int newPos = SetFilePointer(id, pos, NULL, method);
    return newPos;
}

int getFilePos(iaeFileID id)
{   // Если сместится без смещения, то вернется текущая позиция
    return SetFilePointer(id, 0, NULL, FILE_CURRENT);
}

bool closeFileID(iaeFileID id)
{
    return CloseHandle(id);
}

int createDir(char* path)
{
    if(CreateDirectory(path, NULL)) return 1;
    else return GetLastError();
}

int buildDirs(char* path)
{
    strings_t listDirs = utility::getPathes(path);
    for(std::vector<std::string>::iterator i = listDirs.begin(); i!= listDirs.end(); i++)
    {
        if(CreateDirectory((*i).c_str(), NULL)) continue;
        else
        {
            if(GetLastError() == ERROR_ALREADY_EXISTS) continue;
            else return 0;
        }
    }
    return 1;
}

#endif
