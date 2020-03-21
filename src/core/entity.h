#pragma once
#include "maths/glm.h"
#include "utils/constants.h"

struct Entity
{
    glm::vec3 m_Position, m_Rotation, m_Velocity;
    float m_Speed;

    glm::mat4 GetModelMatrix();
    Entity()
        : m_Position(0.0f, 0.0f, 0.0f), m_Rotation(0.0f, 0.0f, 0.0f), m_Velocity(0.0f, 0.0f, 0.0f)
    {
    }
    Entity(glm::vec3 position)
        : m_Position(position), m_Rotation(0.0f, 0.0f, 0.0f), m_Velocity(0.0f, 0.0f, 0.0f)
    {
    }
    Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity) 
        : m_Position(position), m_Rotation(rotation), m_Velocity(velocity)
    {
    }
    Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 velocity, float speed) 
        : m_Position(position), m_Rotation(rotation), m_Velocity(velocity), m_Speed(speed)
    {
    }
    void Move();
    glm::vec3 GetNewPosition();
    glm::vec3 GetAcceleration(glm::vec3 direction);
    void Rotate(float angle, glm::vec3 direction);
    glm::vec3 GetVP(const glm::vec3& normal) const;
};