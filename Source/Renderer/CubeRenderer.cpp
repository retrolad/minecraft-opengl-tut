#include "CubeRenderer.h"
#include "World/Block/BlockDatabase.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw/glfw3.h>
#include <iostream>

CubeRenderer::CubeRenderer()
   : m_textureAtlas("DefaultPack.png")
{
    std::vector<GLfloat> vertexPositions = {

        // Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1 ,0,

        // Front 
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        // Bottom 
        0, 0, 0, 
        1, 0, 0,
        1, 0, 1,
        0, 0, 1,

        // Upper 
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,

        // Left 
        0, 0, 0, 
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,

        // Right
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1
    };

    std::vector<GLfloat> textureCoords;

    auto top = m_textureAtlas.getTexture({BlockDatabase::get().getData(BlockId::Grass).getBlockData().topCoords.x, BlockDatabase::get().getData(BlockId::Grass).getBlockData().topCoords.y});
    auto side = m_textureAtlas.getTexture({BlockDatabase::get().getData(BlockId::Grass).getBlockData().sideCoords.x, BlockDatabase::get().getData(BlockId::Grass).getBlockData().sideCoords.y});
    auto bottom = m_textureAtlas.getTexture({BlockDatabase::get().getData(BlockId::Grass).getBlockData().bottomCoords.x, BlockDatabase::get().getData(BlockId::Grass).getBlockData().bottomCoords.y});

    textureCoords.insert(textureCoords.end(), side.begin(), side.end());
    textureCoords.insert(textureCoords.end(), side.begin(), side.end());
    textureCoords.insert(textureCoords.end(), bottom.begin(), bottom.end());
    textureCoords.insert(textureCoords.end(), top.begin(), top.end());
    textureCoords.insert(textureCoords.end(), side.begin(), side.end());
    textureCoords.insert(textureCoords.end(), side.begin(), side.end());

    // std::vector<GLfloat> textureCoords = {
    //     0, 0,
    //     1, 0,
    //     1, 1,
    //     0, 1,

    //     0, 0,
    //     1, 0,
    //     1, 1,
    //     0, 1,

    //     0, 0,
    //     1, 0,
    //     1, 1,
    //     0, 1,

    //     0, 0,
    //     1, 0,
    //     1, 1,
    //     0, 1,

    //     0, 0,
    //     1, 0,
    //     1, 1,
    //     0, 1,

    //     0, 0,
    //     1, 0,
    //     1, 1,
    //     0, 1,
    // };

    std::vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,  
    
        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16, 
    
        20, 21, 22,
        22, 23, 20
    };

    m_model.construct({vertexPositions, textureCoords, indices});
}

void CubeRenderer::render(const Camera& camera)
{
    m_shader.use();
    m_textureAtlas.Bind(0);
    // TODO bind vao

    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f + 3*sin(glfwGetTime())));
    // glUniformMatrix4fv(glGetUniformLocation(m_shader.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    m_shader.setProjectionViewMatrix(camera.getProjectionMatrix() * camera.getViewMatrix());
    
    glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}