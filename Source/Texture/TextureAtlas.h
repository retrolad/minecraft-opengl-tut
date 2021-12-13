#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include "Texture.h"
#include <vector>

class TextureAtlas : public Texture
{
    public:
        TextureAtlas(const std::string& fileName);

        std::vector<GLfloat> getTexture(const std::vector<GLuint>& coords);

    private:
        int m_imageSize = 256;
        int m_subTextureSize = 16;
};

#endif