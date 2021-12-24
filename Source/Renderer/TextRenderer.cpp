#include "TextRenderer.h"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <stdexcept>
#include <vector>

TextRenderer::TextRenderer()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::load(std::string font, unsigned int fontSize)
{
    FT_Error err;
    FT_Library ft;
    FT_Face face;

    // If error occurred, FT returns non-zero value.
    if(err = FT_Init_FreeType(&ft))
    {
        throw std::runtime_error("Failed to initialize FreeType library");
        return;
    }

    if(err = FT_New_Face(ft, ("../Resources/Fonts/" + font + ".ttf").c_str(), 0, &face))
    {
        throw std::runtime_error("[FT_ERROR: " + std::to_string(err) + "] Failed to load font: " + font);
        return;
    }

    // Sets font's width and height.
    // Setting width to 0 les the face dynamically 
    // calculate the width based on the height 
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    /**
     * OpenGL requires that textures all have a 4-byte alignment e.g. 
     * their size is always a multiple of 4 bytes. Normally this won't 
     * be a problem since most textures have a width that is a multiple
     *  of 4 and/or use 4 bytes per pixel, but since we now only use 
     * a single byte per pixel, the texture can have any possible width. 
     * By setting its unpack alignment to 1 we ensure there are no 
     * alignment issues (which could cause segmentation faults).
     */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load ASCII character set
    for(unsigned char c = 0; c < 128; c++)
    {
        // Load character glyph
        if(err = FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "[FT_ERROR: " << err << "] Failed to load glyph: " << c << std::endl;
            // throw std::runtime_error("[FT_ERROR: " + std::to_string(err) + "] Failed to load glyph: " + std::to_string(c));
            continue;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 
            0, 
            GL_RED, 
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character ch = {
            textureID,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left,  face->glyph->bitmap_top),
            (int)(face->glyph->advance.x)
        };

        m_characters.insert(std::make_pair(c, ch));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // Clear FreeType's resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::addText(const Text& text)
{
    m_texts.push_back(text);
}

void TextRenderer::render()
{
    m_shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    for(auto& text : m_texts)
    {
        float x = text.x;

        m_shader.setProjectionMatrix();
        m_shader.setTextColor({text.color.r, text.color.g, text.color.b});
        
        for(std::string::const_iterator c = text.content.begin(); c != text.content.end(); c++)
        {
            Character ch = m_characters[*c];

            float xpos = x + ch.bearing.x * text.scale;
            float ypos = text.y - (ch.size.y - ch.bearing.y) * text.scale;

            float w = ch.size.x * text.scale;
            float h = ch.size.y * text.scale;

            GLfloat vertices[6][4] = {
                {xpos,       ypos + h,   0.0f, 0.0f},
                {xpos,       ypos,       0.0f, 1.0f},
                {xpos + w,   ypos,       1.0f, 1.0f},

                {xpos,       ypos + h,   0.0f, 0.0f}, 
                {xpos + w,   ypos,       1.0f, 1.0f},
                {xpos + w,   ypos + h,   1.0f, 0.0f} 
            };

            glBindTexture(GL_TEXTURE_2D, ch.textureID); 
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.advance >> 6) * text.scale;
        }
    }

    m_texts.clear();

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}