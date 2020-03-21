#pragma once
#include "maths/glm.h"
#include <array>

class Entity;

enum Planes{
    Near,
    Far,
    Left,
    Right,
    Top,
    Bottom
};

struct Plane{
    glm::vec3 normal;
    float DistanceToPoint(const glm::vec3& point) const;
    float m_DistanceToOrigin;
};

class ViewFrustum{
public:
    void Update(const glm::mat4& mat);
    bool IsInFrustum(const Entity& element) const;
private:
    std::array<Plane, 6> m_Planes;
};