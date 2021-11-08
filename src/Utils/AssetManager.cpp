#include "AssetManager.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;

AssetManager::AssetManager(const char* path)
{
    AssetManager::m_rootPath = path;
    LoadDir(path);
    AddVisitedPath(path);
}

void AssetManager::LoadDir(const std::string path)
{
    Reset();
    AssetManager::m_currentPath = path;
    
    for(const auto& entry : fs::directory_iterator(path))
    {
        std::string extension = entry.path().extension();
        std::string entryPath = entry.path();
        std::string type = GetFileType(entryPath);
        
        Asset asset;
        asset.name = entry.path().filename();
        asset.path = entry.path();
        asset.relativePath = entry.path().relative_path();
        asset.extension = entry.path().extension();
        asset.type = type;
        
        AssetManager::m_assets.push_back(asset);
        
    }
}

void AssetManager::AddVisitedPath(const std::string path)
{
    fs::path fsPath = fs::path(path);
    
    Path dirPath;
    dirPath.stem = fsPath.stem();
    dirPath.path = path;
    path == AssetManager::m_rootPath ? dirPath.isRootPath = true : dirPath.isRootPath = false;
    
    AssetManager::m_visitedPaths.push_back(dirPath);
}

void AssetManager::DeleteLastVisitedPath()
{
    AssetManager::m_visitedPaths.pop_back();
}

void AssetManager::Reset()
{
    AssetManager::m_assets.clear();
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
