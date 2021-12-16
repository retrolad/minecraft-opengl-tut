#include "BlockData.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

BlockData::BlockData(const std::string& fileName)
{
    std::ifstream ifstrm("../Resources/Blocks/" + fileName + ".block");

    if(!ifstrm.is_open())
    {
        throw std::runtime_error("Failed to load file: " + fileName);
    }

    std::string line;
    while(std::getline(ifstrm, line))
    {
        if(line == "Top")
        {
            int x,y;
            ifstrm >> x >> y;   
            m_data.topCoords = {x,y};
        }
        else if(line == "Side")
        {
            int x,y;
            ifstrm >> x >> y;   
            m_data.sideCoords = {x,y};
        } 
        else if(line == "Bottom")
        {
            int x,y;
            ifstrm >> x >> y;   
            m_data.bottomCoords = {x,y};
        }
        else if(line == "All")
        {
            int x,y;
            ifstrm >> x >> y;   
            m_data.topCoords = {x,y};
            m_data.sideCoords = {x,y};
            m_data.bottomCoords = {x,y};
        }
    }
}

const BlockDataStorage& BlockData::getBlockData() const
{
    return m_data;
}