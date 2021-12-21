#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"

#include <GLFW/glfw3.h>

class World;

class Player : public Entity
{
    public:
        Player(World* world);
        
        void handleInput(GLFWwindow* window);
        
        void keyboardInput(GLFWwindow* window);
        void mouseInput(GLFWwindow* window);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    
        void update(float deltaTime);

    private:
        glm::vec3 m_direction;
        World* m_world;
};

#endif

