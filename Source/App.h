#ifndef APP_H
#define APP_H

#include "Renderer/Renderer.h"
#include "Context.h"
#include "Camera.h"
#include "Player/Player.h"

class App
{
public:
    App();

    void run();
    void handleEvents(float deltaTime);
    bool isKeyPressed(int keyCode);

private:
    Context m_context;
    Renderer m_renderer;    
    Camera m_camera;

    Player m_player;
};

#endif