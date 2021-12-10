#include "Camera.h"

Camera::Camera()
{
    m_projectionMatrix = glm::perspective(glm::radians(90.0f), 1280.0f/720.0f, 0.1f, 100.0f);

    m_worldPosition = {0, 0, 3};

    directionVector = {0, 0, -1};
    upVector        = {0, 1,  0};

    yaw = -90.0f;
    pitch = 0.0f;
    camSpeed = 5.0f;

    update();
}

void Camera::processInput(CameraMovement direction, float deltaTime)
{
    float camVelocity = camSpeed * deltaTime;
    
    if(direction == FORWARD)
        m_worldPosition += camVelocity * directionVector;
    if(direction == BACKWARD)
        m_worldPosition -= camVelocity * directionVector;
    if(direction == RIGHT)
        m_worldPosition += camVelocity * rightVector;
    if(direction == LEFT)
        m_worldPosition -= camVelocity * rightVector;
}

void Camera::update()
{
    // Create right vector
    rightVector = glm::normalize(glm::cross(directionVector, upVector));
    m_viewMatrix = glm::lookAt(m_worldPosition, m_worldPosition + directionVector, upVector);
}

const glm::mat4& Camera::getProjectionMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return m_viewMatrix;
}
