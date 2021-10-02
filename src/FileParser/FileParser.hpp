#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int CanOpenFile(std::ifstream& file, const char* filePath)
{
    if(!file.is_open()){
        std::cout << "Failed to open " << filePath << std::endl;
        return -1;
    } else {
        return 1;
    }
}

std::string ParseContentsFromFilePath(const char* filePath)
{
    std::string fileContent;
    
    std::ifstream file (filePath);
    int isValidFilePath = CanOpenFile(file, filePath);
    
    if(isValidFilePath){
        file.open(filePath);
        std::stringstream fileContentStream;

        fileContentStream << file.rdbuf();
        fileContent = fileContentStream.str();
        
        file.close();
    }
    
    return fileContent;
}


