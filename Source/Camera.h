#ifndef CAMERA_H
#define CAMERA_H

#include "Maths/glm.h"
#include "Entity.h"

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    public:
        Camera();

        void update();
        void processInput(CameraMovement direction,float deltaTime);

        const glm::mat4& getViewMatrix()         const noexcept;
        const glm::mat4& getProjectionMatrix()   const noexcept;

        void bindEntity(const Entity& entity);
    private:
        const Entity* m_pEntity;

        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;

        glm::vec3 m_position;
        glm::vec3 m_rotation;

        glm::vec3 upVector;
        glm::vec3 directionVector;
        glm::vec3 rightVector;

        float camSpeed;
};

#endif