#pragma once
#include "../../src/Utils/AssetManager.hpp"
#include "../../src/Textures/Texture.hpp"

class ContentBrowserPanel
{
public:
    ContentBrowserPanel();
    void OnImGuiRender();
    
private:
    unsigned int m_fileIcon;
    unsigned int m_folderIcon;
};
