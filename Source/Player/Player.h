#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"

#include <GLFW/glfw3.h>

class Player : public Entity
{
    public:
        Player();
        
        void handleInput(GLFWwindow* window);
        
        void keyboardInput(GLFWwindow* window);
        void mouseInput();

        void update(float deltaTime);

    private:
        glm::vec3 m_direction;
};

#endif

