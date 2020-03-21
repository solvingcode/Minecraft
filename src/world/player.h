#pragma once

#include "core/entity.h"

class World;
class Window;

class Player : public Entity {
public:
    Player();
    ~Player();
    void Collide(World& world, glm::vec3 velocity);
    void Update(World& world);
    void Move(glm::vec3 direction);
    void Jump();
    void HandleInput(Window& window);
    bool IsUnderWater();
    void SetUnderWater(bool underwater);
private:
    glm::vec3 m_Acceleration;
    bool m_OnGround = true;
    bool m_IsFly = false;
    bool m_IsUnderWater = false;
};