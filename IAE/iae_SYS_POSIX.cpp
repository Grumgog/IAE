
iaeFileID getFileID(char* path, int mode);
int fwrite(iaeFileID id, void* buff, int size);
int fread(iaeFileID id, void* buff, int size);
int setFilePos(iaeFileID id, int pos, int mode);
int getFilePos(iaeFileID id);
bool closeFileID(iaeFileID id);
