#include "AssetManager.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;

AssetManager::AssetManager(const char* path)
{
    for(const auto &entry : fs::directory_iterator(path))
    {
        std::string extension = entry.path().extension();
        std::string entryPath = entry.path();
        std::string type = GetFileType(entryPath);
        
        Asset asset;
        asset.name = entry.path().filename();
        asset.path = entry.path();
        asset.extension = entry.path().extension();
        asset.type = type;
        
        AssetManager::m_assets.push_back(asset);
        
    }
}

std::string AssetManager::GetFileType(std::string& path)
{
    fs::file_status status = fs::status(path);
    switch(status.type())
    {
        case fs::file_type::directory: return "dir";
            break;
        default: return "file";
    }
}
