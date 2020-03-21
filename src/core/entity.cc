#include "entity.h"

glm::mat4 Entity::GetModelMatrix()
{
    glm::mat4 matrix(1.0f);
    
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, m_Position);

    return matrix;
}

void Entity::Move(){
    m_Position = GetNewPosition();
}

glm::vec3 Entity::GetNewPosition(){
    glm::vec3 newPosition = m_Position;
    float yaw = m_Rotation.y;
    float pitch = m_Rotation.x;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw));
    front.y = 0;
    front.z = sin(glm::radians(yaw));
    glm::vec3 cameraFront = glm::normalize(front);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    if(m_Velocity.z != 0){
        newPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * m_Velocity.z;
    }
    if(m_Velocity.x != 0){
        newPosition += cameraFront * m_Velocity.x;
    }
    if(m_Velocity.y != 0){
        newPosition += cameraUp * m_Velocity.y;
    }

    return newPosition;
}

glm::vec3 Entity::GetAcceleration(glm::vec3 direction){
    glm::vec3 newAcceleration(0.f);
    float yaw = m_Rotation.y;
    float pitch = m_Rotation.x;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw));
    front.y = 0;
    front.z = sin(glm::radians(yaw));
    glm::vec3 cameraFront = glm::normalize(front);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    if(direction.z != 0){
        newAcceleration += glm::normalize(glm::cross(cameraFront, cameraUp)) * (direction.z * m_Speed);
    }
    if(direction.x != 0){
        newAcceleration += cameraFront * (direction.x * m_Speed);
    }
    if(direction.y != 0){
        newAcceleration += cameraUp * (direction.y * m_Speed);
    }

    return newAcceleration;
}

void Entity::Rotate(float angle, glm::vec3 direction){
    glm::mat4 matrix(1.0f);
    glm::vec4 rotation = glm::vec4(m_Rotation.x + direction.x * angle, m_Rotation.y + direction.y * angle, m_Rotation.z + direction.z * angle, 1.0f);
    if(rotation[0] <= 90.0f && rotation[0] >= -90.0f){
        m_Rotation = rotation;
    }
}

glm::vec3 Entity::GetVP(const glm::vec3& normal) const
    {
        glm::vec3 res = m_Position;
        glm::vec3 dimensions = {CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE};

        if (normal.x > 0)
        {
            res.x += dimensions.x;
        }
        if (normal.y > 0)
        {
            res.y += dimensions.y;
        }
        if (normal.z > 0)
        {
            res.z += dimensions.z;
        }

        return res;
    }