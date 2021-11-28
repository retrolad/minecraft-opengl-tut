#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string GetFileContent(const std::string& filePath)
{
    std::ifstream ifstrm(filePath);

    if(!ifstrm.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::stringstream ss;

    // Read 
    ss << ifstrm.rdbuf();
    ifstrm.close();
    return ss.str();
}

