#include "glad/glad.h"
#include "Context.h"

#include <stdexcept>

Context::Context()
{
    // Initialize glfw library
    glfwInit();

    // Configure GLFW by setting hints
    // Configuration will be used with next glfwCreateWindow call
    // We use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // We use core-profile and do not want backwards compability with OpenGL <= 3.2
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window object and its associated context
    window = glfwCreateWindow(1280, 720, "Minecraft OpenGL", NULL, NULL);

    if(window == NULL)
    {
        // Destroy all windows and free resources
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make this window's context current for the calling thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    // We pass a function that can load addresses of OpenGL functions
    // That function will be our OpenGL functions loader
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Specify rendering window sizes with respect to the window
    // From lower-left corner with width and height
    // OpenGL will map its normalized device coordinates (from -1 to 1) 
    // to the window coordinates (0,0)
    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);
}

Context::~Context()
{
    glfwDestroyWindow(window);
}