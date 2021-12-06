#ifndef APP_H
#define APP_H

#include "Renderer/Renderer.h"
#include "Context.h"

class App
{
public:
    App() = default;

    void run();

private:
    Context m_context;
    Renderer m_renderer;    
};

#endif