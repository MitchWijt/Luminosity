#include "AssetManager.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;

AssetManager::AssetManager(const char* path)
{
    for(const auto &entry : fs::directory_iterator(path))
    {
        std::string extension = entry.path().extension();
        if(extension == ".jpeg" || extension == ".png")
        {
            File file;
            file.fileName = entry.path().filename();
            file.filePath = entry.path();
            file.extension = entry.path().extension();
            
            AssetManager::m_filePaths.push_back(file);
        }
    }
}
