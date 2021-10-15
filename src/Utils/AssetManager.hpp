#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::__fs::filesystem;

struct File
{
    std::string fileName;
    std::string filePath;
};

class AssetManager
{
public:
    AssetManager(const char* path)
    {
        for(const auto &entry : fs::directory_iterator(path))
        {
            std::string extension = entry.path().extension();
            if(extension == ".jpeg" || extension == ".png")
            {
                File file;
                file.fileName = entry.path().filename();
                file.filePath = entry.path();
                
                m_filePaths.push_back(file);
            }
        }
           
    }
public:
    std::vector<File> m_filePaths;
};
