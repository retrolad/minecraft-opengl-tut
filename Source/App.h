#ifndef APP_H
#define APP_H

#include "Renderer/Renderer.h"
#include "Context.h"
#include "Camera.h"
#include "Player/Player.h"
#include "World/Chunk/ChunkSection.h"
#include "World/World.h"
#include "Utils/FPSCounter.h"

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

    World m_world;
    
    Player m_player;

    FPSCounter m_fpsCounter;
    // ChunkSection m_chunk;
};

#endif