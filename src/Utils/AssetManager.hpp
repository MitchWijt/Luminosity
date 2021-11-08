#pragma once

#include <iostream>
#include <vector>

namespace fs = std::__fs::filesystem;

struct Asset
{
    std::string name;
    std::string path;
    std::string relativePath;
    std::string extension;
    std::string type;
};

struct Path
{
    std::string stem;
    std::string path;
    bool isRootPath;
};

class AssetManager
{
public:
    AssetManager(const char* path);
    std::string GetFileType(std::string& path);
    void LoadDir(const std::string path);
    void AddVisitedPath(const std::string path);
    void DeleteLastVisitedPath();
    void Reset();
public:
    std::string m_rootPath;
    std::string m_currentPath;
    std::vector<Asset> m_assets;
    std::vector<Path> m_visitedPaths;
};
