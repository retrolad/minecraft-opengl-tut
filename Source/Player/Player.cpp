#include "../World/World.h"
#include "Player.h"

#include <iostream>

Player::Player(World* world)
: m_world(world),
  m_direction(glm::vec3(0, 0, 0))
{
    position  = {-1, CHUNK_SIZE * 3.5f, -1};
    // position  = {0, 0, 0};
    rotation  = {0, 0, 0};
    front     = {0, 0, -1};
    up        = {0, 1, 0};
    right     = glm::cross(front, up);

}

void Player::update(float deltaTime)
{
    position += m_direction * deltaTime;
    right = glm::normalize(glm::cross(front, up));

    m_direction = {0,0,0};

    // std::cout << "[" << front.x << "," << front.y << "," << front.z << "]" << std::endl; 
}

void Player::handleInput(GLFWwindow* window)
{
    keyboardInput(window);
    mouseInput(window);
}

void Player::keyboardInput(GLFWwindow* window)
{
    float speed = 5.0f;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
    {
        speed = 20.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP))
    {
        m_direction += front * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))
    {
        m_direction -= front * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))
    {
        m_direction += right * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))
    {
        m_direction -= right * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE))
    {
        m_direction += glm::vec3{0, 5, 0} * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_I))
    {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        std::cout << "Player position: " << "[" << position.x << "," << position.y << "," << position.z << "]\n";
        std::cout << "Camera rotation: " << "[" << rotation.x << "," << rotation.y << "," << rotation.z << "]\n";
        std::cout << "Camera direction: " << "[" << front.x << "," << front.y << "," << front.z << "]\n";
    }
}

void Player::mouseInput(GLFWwindow* window)
{
    static double start = glfwGetTime();
    for(auto ray = front; glm::length(ray) < 3.0f; ray += front * 0.6f)
    {
        auto rayEnd = position + ray;
        auto block = m_world->getBlock(rayEnd.x, rayEnd.y, rayEnd.z);
        
        if(block != 0)
        {
            if(glfwGetTime() - start > 0.1)
            {
                if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                {
                    // std::cout << "Block hit by ray cast\n";
                    m_world->editBlock(rayEnd.x, rayEnd.y, rayEnd.z, BlockId::Void);
                    
                    start = glfwGetTime();
                    break;
                }
                else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
                {
                    // std::cout << "Block hit by ray cast\n";
                    m_world->editBlock(rayEnd.x, rayEnd.y, rayEnd.z, BlockId::Dirt);
                
                    start = glfwGetTime();
                    break;
                }
            }
        }
        // start = glfwGetTime();
    }

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    static double lastX = xPos, lastY = yPos;
    static const double VERTICAL_BOUND = 89.0f;

    double xOffset = xPos - lastX;
    double yOffset = lastY - yPos;

    rotation.x += xOffset * 0.05f;
    rotation.y += yOffset * 0.05f;

    if(rotation.y > VERTICAL_BOUND) rotation.y = VERTICAL_BOUND;
    if(rotation.y < -VERTICAL_BOUND) rotation.y = -VERTICAL_BOUND;

    if(rotation.x > 180.0f) rotation.x = -180.0f;
    if(rotation.x < -180.0f) rotation.x = 180.0f;

    front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
    front.y = sin(glm::radians(rotation.y));
    front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

    front = glm::normalize(front);

    glfwSetCursorPos(window, 640, 360);
    glfwGetCursorPos(window, &lastX, &lastY);
}   

void Player::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // std::cout << "Handled button: " << button << "\nAction: " << action << std::endl;
    // If left button is down
    if(button == 0 && action == 1)
    {
        // auto ray = front * 5;
    }
}
