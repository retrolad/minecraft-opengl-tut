#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    private:
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;

        glm::vec3 m_worldPosition;

        glm::vec3 upVector;
        glm::vec3 directionVector;
        glm::vec3 rightVector;

        float yaw;
        float pitch; 
        float camSpeed;
};

#endif