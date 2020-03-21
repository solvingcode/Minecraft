#pragma once
#include "entity.h"
#include "world/player.h"
#include "utils/constants.h"
#include "utils/log.h"
#include <iostream>
#include <array>
#include "view-frustum.h"

class Player;

class Camera : public Entity
{
public:
    Camera(float fov, float znear, float zfar);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetViewMatrixRotation();
    glm::mat4 GetProjectionMatrix();
    glm::vec3 GetRay();
    void Update(Player &player);
    void UpdateGeoInfo(Player &player);
    const ViewFrustum& GetViewFrustum() const;
    ~Camera();

private:
    float m_Fov, m_Znear, m_Zfar;
    Player *m_Player;
    ViewFrustum m_ViewFrustum;
};
