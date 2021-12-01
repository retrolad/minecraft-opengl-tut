#pragma once
#ifndef RTEXCEPT_H
#define RTEXCEPT_H

#include <csignal>
#include <iostream>
#include <glad/glad.h>

#define ASSERT(x)  if (!(x)) std::raise(SIGINT)
#define GL(x) GLClearError();\
    x;\
    ASSERT(GLLog(#x, __FILE__, __LINE__))

static void GLClearError()
{
    // Skip all errors
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLog(const char* function, const char* file, int line)
{
    GLenum error;
    while(error = glGetError())
    {
        std::cout << "[OpenGL Error]: " << error << " in " << function << " " << file << " " << line << std::endl;
        return false; 
    }

    return true;
}
#endif