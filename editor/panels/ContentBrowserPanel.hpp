#pragma once
#include "../../src/Utils/AssetManager.hpp"
#include "../../src/Textures/Texture.hpp"

class ContentBrowserPanel
{
public:
    ContentBrowserPanel();
    
    // TODO:: Texture process needs to be separated from the asset manager process
    void OnImGuiRender();
    
private:
    unsigned int m_fileIcon;
    unsigned int m_folderIcon;
};
