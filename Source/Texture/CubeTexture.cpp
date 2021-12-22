#include "CubeTexture.h"

#include "../Utils/stb_image.h"

#include <stdexcept>

CubeTexture::CubeTexture(const std::vector<std::string>& faces)
: m_faces(faces)
{
    loadCubemap();
}

CubeTexture::~CubeTexture()
{
    glDeleteTextures(1, &m_id);
}

void CubeTexture::loadCubemap()
{
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

    // Order of cubemap texture enums
    // GL_TEXTURE_CUBE_MAP_POSITIVE_X	Right
    // GL_TEXTURE_CUBE_MAP_NEGATIVE_X	Left
    // GL_TEXTURE_CUBE_MAP_POSITIVE_Y	Top
    // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	Bottom
    // GL_TEXTURE_CUBE_MAP_POSITIVE_Z	Back
    // GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	Front
    int width, height, BPP;
    for(int i = 0; i < m_faces.size(); i++)
    {
        GLenum format;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* buffer = stbi_load(("../Resources/Textures/" + m_faces[i]).c_str(), &width, &height, &BPP, 0);
        
        if(BPP == 3)
            format = GL_RGB;
        else if(BPP == 4)
            format = GL_RGBA;

        if(buffer)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 
                         width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
            stbi_image_free(buffer);
        }
        else
        {
            throw std::runtime_error("Failed to load cubemap texture: " + m_faces[i]);
            stbi_image_free(buffer);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeTexture::bindTexture() const
{
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}