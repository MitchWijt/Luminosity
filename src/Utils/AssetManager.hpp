#include <iostream>
#include <vector>

namespace fs = std::__fs::filesystem;

struct Asset
{
    std::string name;
    std::string path;
    std::string extension;
    std::string type;
};

class AssetManager
{
public:
    AssetManager(const char* path);
    std::string GetFileType(std::string& path);
public:
    std::vector<Asset> m_assets;
};
