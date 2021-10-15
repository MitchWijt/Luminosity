#include <iostream>
#include <vector>

struct File
{
    std::string fileName;
    std::string filePath;
    std::string extension;
};

class AssetManager
{
public:
    AssetManager(const char* path);
public:
    std::vector<File> m_filePaths;
};
