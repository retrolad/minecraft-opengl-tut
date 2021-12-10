#ifndef ENTITY_H
#define ENTITY_H

#include "Maths/glm.h"

struct Entity
{
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    // {yaw, pitch, 0}
    glm::vec3 rotation;
};

#endif 