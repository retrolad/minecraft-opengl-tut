#include <stdexcept>
#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& path)
    : m_FilePath(path), m_Width(0), m_Height(0)
{
    loadFromFile(path);
}

Texture::~Texture()
{
    // Delete texture from the gpu
    glDeleteTextures(1, &m_id);
}

void Texture::loadFromFile(const std::string& path)
{
    // Flip image to show up properly 
    stbi_set_flip_vertically_on_load(true);

    // Generate texture object
    glGenTextures(1, &m_id);
    // Bind texture object
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    // Load image
    m_Buffer = stbi_load(("../Resources/Textures/" + path).c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // Texture wrapping (x,y wrapping)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Texture filtering
    // Use linear interpolation between the two closest mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if(!m_Buffer)
    {
        throw std::runtime_error("Failed to load texture1");
    }

    // Generate the texture image on the currently bound texture
    // object
    /** 
     * target - 
     * level - level of detail (LOD)
     * internalformat - number of color components in the texture (how OpenGL will store the texture data)
     * width
     * height
     * border - should always be 0 (legacy)
     * format - format of the pixel data (we're providing OpenGL with)
     * type - the data type of the pixel data (we loaded image as rgb and stored
     *        in unsigned char* (bytes))
     * data - a pointer to the image data
    */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer);
    // Unbind
    glBindTexture(GL_TEXTURE_2D, 0);

    // Automatically generate all the required mipmaps for the currently bound texture
    // glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image memory
    stbi_image_free(m_Buffer);
    
}

void Texture::Bind(unsigned int slot) const
{
    // Activate texture at slot <slot>
    glActiveTexture(GL_TEXTURE + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}