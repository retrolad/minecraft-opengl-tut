#include "FPSCounter.h"

#include "../Renderer/Renderer.h"

FPSCounter::FPSCounter()
: m_fps(0),
  m_fpsCounter(0),
  m_text({"FPS: " + m_fpsCounter, 20.0f, 680.0f, 1.3f, {1.0f, 0.0f, 1.0f}})
{
    frameTime = glfwGetTime();
}

void FPSCounter::render(Renderer& renderer)
{
    update();
    renderer.drawText(m_text);
}

void FPSCounter::update()
{
    m_fpsCounter++;
    double elapsedTime = glfwGetTime() - frameTime;
    if(elapsedTime > 0.5)
    {
        m_text.content = "FPS: " + std::to_string((int)(m_fpsCounter / elapsedTime));
        frameTime = glfwGetTime();
        m_fpsCounter = 0;
    }
    // frameTime = glfwGetTime() - frameTime;
}