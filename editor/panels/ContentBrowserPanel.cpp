#include "../../src/lheaders.hpp"
#include "ContentBrowserPanel.hpp"
#include <filesystem>
#include "../../libs/imgui/imgui.h"

#include "../../src/Utils/AssetManager.hpp"
#include "../../src/Textures/Texture.hpp"

namespace fs = std::__fs::filesystem;

const char* g_assetPath = "../assets";
AssetManager g_assets = AssetManager(g_assetPath);

ContentBrowserPanel::ContentBrowserPanel()
{
    Texture2D folderIcon = Texture2D();
    folderIcon.Create("../editor/assets/folder.png", ".png");
    folderIcon.Load();
    m_folderIcon = folderIcon.m_textureId;
    
    Texture2D fileIcon = Texture2D();
    fileIcon.Create("../editor/assets/file.png", ".png");
    fileIcon.Load();
    m_fileIcon = fileIcon.m_textureId;
}

void ContentBrowserPanel::OnImGuiRender()
{
    ImGui::Begin("Assets");
    for(int i = 0; i < g_assets.m_visitedPaths.size(); i++)
    {
        std::string& dirPath = g_assets.m_visitedPaths[i].path;
        std::string& dirName = g_assets.m_visitedPaths[i].stem;
        
        ImGui::SameLine();
        if(ImGui::Button(dirName.c_str()))
        {
            if(dirPath != g_assets.m_currentPath)
                g_assets.DeleteLastVisitedPath();
            
            g_assets.LoadDir(dirPath.c_str());
        }
    }

    for (int i = 0; i < g_assets.m_assets.size(); i++)
    {
        std::string extension = g_assets.m_assets[i].extension;
        std::string path = g_assets.m_assets[i].path;
        std::string name = g_assets.m_assets[i].name;
        std::string type = g_assets.m_assets[i].type;
        
        ImGui::PushID(i);
        if(i % 10 == 0) ImGui::NewLine();
        ImGui::SameLine();
        
        if(type == "dir")
        {
            
            ImGui::ImageButtonWithText((void*)(intptr_t)m_folderIcon, name.c_str(), ImVec2(50.0f, 50.0f));
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                g_assets.LoadDir(path.c_str());
                g_assets.AddVisitedPath(path);
            }
        } else
        {
            ImGui::ImageButtonWithText((void*)(intptr_t)m_fileIcon, name.c_str(), ImVec2(50.0f, 50.0f));
            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", path.c_str(), sizeof(path));
                ImGui::EndDragDropSource();
            }
        }
        
        ImGui::PopID();
    };
    ImGui::End();
}


