#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <string>

#include "Text.h"

class Renderer;

class FPSCounter
{
    public:
        FPSCounter();

        void render(Renderer& renderer);

        void update();

    private:
        double frameTime;
        int m_fps;
        int m_fpsCounter;
        Text m_text;
};

#endif // FPSCOUNTER_H
