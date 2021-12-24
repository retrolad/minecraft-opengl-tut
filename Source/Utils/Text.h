#ifndef TEXT_H
#define TEXT_H

#include <string>

struct TextColor
{
    float r;
    float g;
    float b;
};

struct Text
{
    std::string content;
    float x;
    float y;
    float scale;
    TextColor color;
};

#endif // TEXT_H
