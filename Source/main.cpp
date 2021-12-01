#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <stdexcept>
#include <iostream>

#include "rtexcept.h"
#include "Shaders/Shader.h"
#include "Texture/Texture.h"

// A window resize callback
// Also called on window creation with the same dimensions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIN_WIDTH = 800;
const unsigned int WIN_HEIGHT = 600;

int main()
{
    // Initialize GLFW library
    glfwInit();

    // Configure GLFW by setting hints
    // Configuration will be used with next glfwCreateWindow call
    // We use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // We use core-profile and do not want backwards compability with OpenGL <= 3.2
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create window object and its associated context
    // 800x600 windowed mode
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Retro Engine 3D", NULL, NULL);
    if(window == NULL)
    {
        throw std::runtime_error("Failed to create GLFW window");
        // Destroy all windows and free resources
        glfwTerminate();
        return -1;
    }

    // Make this window's context current for the calling thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    // We pass a function that can load addresses of OpenGL functions
    // That function will be our OpenGL functions loader
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
        return -1;
    }

    // Specify rendering window sizes with respect to the window
    // From lower-left corner with width and height
    // OpenGL will map its normalized device coordinates (from -1 to 1) 
    // to the window coordinates (0,0)
    // glViewport(0, 0, 800, 600);

    // Set frame buffer resize callback 
    // Will be called on every window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::cout << glGetString(GL_VERSION) << std::endl;

    Shader shaderProgram("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");


    /** TEXTURE */

    Texture texture1("../Resources/Textures/brick.jpg");
    Texture texture2("../Resources/Textures/mu.png");

    /** VERTEX BUFFER OBJECTS (VBO) & VERTEX OBJECT ARRAY (VAO) */

    float vertices[] = {
        // coords           // colors          // texture coords
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    };

    // float vertices[] = {
    //     // first triangle
    //     0.5f,  0.5f, 0.0f,   // верхняя правая
    //     0.5f, -0.5f, 0.0f,   // нижняя правая
    //     -0.5f, -0.5f, 0.0f,  // нижняя левая

    //     // second triangle
    //     0.5f,  0.5f, 0.0f,   // верхняя правая
    //     -0.5f, -0.5f, 0.0f,  // нижняя левая
    //     -0.5f,  0.5f, 0.0f   // верхняя левая 
    // };

    // Index buffer data
    // OpenGL draws in clockwise order
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generate buffer object to store vertices
    GLuint VBO, VAO, EBO;

    // Generate vertex buffer and vertex array
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind buffer to target type
    // We want vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Allocate memory and initialize that memory with our vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and initialize index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /** VERTEX ATTRIBUTES LINKING */

    // Specify how OpenGL should interpret the vertex buffer data whenever a drawing call
    // made (layout of vertex buffer). The interpretation specified is stored in currently bound VAO. So this links
    // VBO with VAO
    /** 
     * index -      Vertex attribute index. We specified position as first attribute 
     *               in the vertex shader (layout(location=0)). We want to pass data 
     *               to this attribute, so we pass in 0
     * size  -      Number of components in vertex attribute. The vertex attribute is
     *               vec3
     * type  -      The type of of the data. vec* in GLSL consists of floating-point 
     *               values 
     * notmalized - Whether data should be normalized. This is relevant if we pass 
     *               integer value. We pass float, so false
     * stride     - This is known as the space between consecutive vertex attributes.
     *               The next set of position data is located exactly 3 times the size
     *               of a float away. Our array is tightly packed (there is no space
     *               between the next vertex attribute), so we also could specify 0
     *               to let OpenGl determine the stride
     * pointer    - The offset of where the position data begins in the buffer. Just 0
     *              in our case
     */
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    // Enable vertex attribute
    glEnableVertexAttribArray(0);

    // Color attribute
    // Color has 3 components
    // There is 8 * sizeof(float) bytes between every color attributes
    // Color attribute begins at 3 * sizeof(float)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    // Has 2 components
    // Texture attribute begins at 6 * sizeof(float)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Draw as lines (wireframe mode). Apply to front and back triangles
    // of a polygon
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Tell OpenGL to which texure unit each shader sampler belongs to
    // Only need to set this once
    // Activate shader before setting uniforms
    shaderProgram.use();
    // Set by hand
    glUniform1i(glGetUniformLocation(shaderProgram.getID(), "texture1"), 0);
    // Or via our shader class
    shaderProgram.setInt("texture2", 1);

    /** RENDER LOOP */

    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering commands

        // Set color, which will be used to clear buffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // Clear specified buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind texture to corresponding textures units
        // Texture units are uniform variables in fragment shader
        texture1.Bind(0);
        //texture2.Bind(1);

        // Should use this every cycle?
        shaderProgram.use();

        float timeValue = glfwGetTime();
        float blueValue = std::sin(timeValue) / 2.0f + 0.5f;
        
        //shaderProgram(vertexColorLocation, 1.0f, 0.5f, blueValue, 1.0f);

        glBindVertexArray(VAO);

        // Draw
        // Primitive type
        // 
        // Number of vertices we want to draw
        // mode - type of primitive
        // start index
        // number of vertices
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // mode - primitive type
        // count - number of elements to draw
        // type - the type of the values in indices
        // pointer - offset in a buffer where the indices are stored
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // Swap back and front buffers
        glfwSwapBuffers(window);
        // Process nad handle window and input events
        glfwPollEvents();
    }

    // Free all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}