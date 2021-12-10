#include "Camera.h"

Camera::Camera()
{
    m_projectionMatrix = glm::perspective(glm::radians(90.0f), 1280.0f/720.0f, 0.1f, 100.0f);

    m_position = {0, 0, 3};

    directionVector = {0, 0, -1};
    upVector        = {0, 1,  0};
    
    camSpeed = 5.0f;

    // update();
}

void Camera::bindEntity(const Entity& entity)
{
    m_pEntity = &entity;
}

void Camera::update()
{
    m_position = m_pEntity->position;
    m_rotation = m_pEntity->rotation;

    // Create right vector
    rightVector = glm::normalize(glm::cross(m_pEntity->front, m_pEntity->up));
    m_viewMatrix = glm::lookAt(m_position, m_position + m_pEntity->front, m_pEntity->up);
}

void Camera::processInput(CameraMovement direction, float deltaTime)
{
    float camVelocity = camSpeed * deltaTime;
    
    if(direction == FORWARD)
        m_position += camVelocity * directionVector;
    if(direction == BACKWARD)
        m_position -= camVelocity * directionVector;
    if(direction == RIGHT)
        m_position += camVelocity * rightVector;
    if(direction == LEFT)
        m_position -= camVelocity * rightVector;
}


const glm::mat4& Camera::getProjectionMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return m_viewMatrix;
}
