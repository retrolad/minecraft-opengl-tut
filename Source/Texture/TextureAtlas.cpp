#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& fileName)
{
    loadFromFile(fileName);
}

std::vector<GLfloat> TextureAtlas::getTexture(const std::vector<GLuint>& coords)
{
    const static GLfloat TEXTURE_SIZE = (GLfloat)m_subTextureSize / (GLfloat)m_imageSize;

    float xMin = coords[0] * TEXTURE_SIZE; 
    float yMin = 1 - coords[1] - TEXTURE_SIZE;

    float xMax = xMin + TEXTURE_SIZE;
    float yMax = yMin + TEXTURE_SIZE;

    return {
        xMin, yMin,
        xMax, yMin,
        xMax, yMax,
        xMin, yMax 
    };
}