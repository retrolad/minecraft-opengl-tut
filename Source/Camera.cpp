#include "Camera.h"

Camera::Camera()
{
    m_projectionMatrix = glm::perspective(glm::radians(75.0f), 1280.0f/720.0f, 0.1f, 1000.0f);

    m_position = {0, 0, 3};
}

void Camera::bindEntity(const Entity& entity)
{
    m_pEntity = &entity;
}

void Camera::update()
{
    m_position = m_pEntity->position;
    m_rotation = m_pEntity->rotation;

    // m_viewMatrix = glm::lookAt(m_position, m_position + m_pEntity->front, m_pEntity->up);
    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::rotate(view, glm::radians(m_rotation.y), {1, 0, 0});
    // view = glm::rotate(view, glm::radians(m_rotation.x), {0, 1, 0});
    // view = glm::rotate(view, glm::radians(m_rotation.z), {0, 0, 1});

    // view = glm::translate(view, m_position);

    m_viewMatrix = glm::lookAt(m_position, m_position + m_pEntity->front, m_pEntity->up);
}

const glm::mat4& Camera::getProjectionMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return m_viewMatrix;
}
