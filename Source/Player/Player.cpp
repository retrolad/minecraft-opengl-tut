#include "Player.h"

#include <iostream>

Player::Player()
{
    position  = {0, 3, 3};
    rotation  = {-90, 0, 0};
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
        speed = 10.0f;
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
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    static double lastX = xPos, lastY = yPos;
    static const double VERTICAL_BOUND = 80.0f;

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