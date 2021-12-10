#include "Player.h"

Player::Player()
{
    position  = {0, 0, 3};
    front     = {0, 0, -1};
    up        = {0, 1, 0};
    right     = glm::cross(front, up);
}

void Player::update(float deltaTime)
{
    position += m_direction * deltaTime;
    right = glm::normalize(glm::cross(front, up));

    m_direction = {0,0,0};
}

void Player::handleInput(GLFWwindow* window)
{
    keyboardInput(window);
}

void Player::keyboardInput(GLFWwindow* window)
{
    const float speed = 5.0f;
    if(glfwGetKey(window, GLFW_KEY_W))
    {
        m_direction += front * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S))
    {
        m_direction -= front * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_D))
    {
        m_direction += right * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_A))
    {
        m_direction -= right * speed;
    }
}

void Player::mouseInput()
{

}