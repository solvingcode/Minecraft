#include "view-frustum.h"
#include "entity.h"

float Plane::DistanceToPoint(const glm::vec3& point) const {
    return glm::dot(point, normal) + m_DistanceToOrigin;
}

void ViewFrustum::Update(const glm::mat4& mat){

    // left
    m_Planes[Planes::Left].normal.x     = mat[0][3] + mat[0][0];
    m_Planes[Planes::Left].normal.y     = mat[1][3] + mat[1][0];
    m_Planes[Planes::Left].normal.z     = mat[2][3] + mat[2][0];
    m_Planes[Planes::Left].m_DistanceToOrigin     = mat[3][3] + mat[3][0];

    // right
    m_Planes[Planes::Right].normal.x    = mat[0][3] - mat[0][0];
    m_Planes[Planes::Right].normal.y    = mat[1][3] - mat[1][0];
    m_Planes[Planes::Right].normal.z    = mat[2][3] - mat[2][0];
    m_Planes[Planes::Right].m_DistanceToOrigin    = mat[3][3] - mat[3][0];

    // bottom
    m_Planes[Planes::Bottom].normal.x   = mat[0][3] + mat[0][1];
    m_Planes[Planes::Bottom].normal.y   = mat[1][3] + mat[1][1];
    m_Planes[Planes::Bottom].normal.z   = mat[2][3] + mat[2][1];
    m_Planes[Planes::Bottom].m_DistanceToOrigin   = mat[3][3] + mat[3][1];

    // top
    m_Planes[Planes::Top].normal.x      = mat[0][3] - mat[0][1];
    m_Planes[Planes::Top].normal.y      = mat[1][3] - mat[1][1];
    m_Planes[Planes::Top].normal.z      = mat[2][3] - mat[2][1];
    m_Planes[Planes::Top].m_DistanceToOrigin      = mat[3][3] - mat[3][1];

    // near
    m_Planes[Planes::Near].normal.x     = mat[0][3] + mat[0][2];
    m_Planes[Planes::Near].normal.y     = mat[1][3] + mat[1][2];
    m_Planes[Planes::Near].normal.z     = mat[2][3] + mat[2][2];
    m_Planes[Planes::Near].m_DistanceToOrigin     = mat[3][3] + mat[3][2];

    // far
    m_Planes[Planes::Far].normal.x      = mat[0][3] - mat[0][2];
    m_Planes[Planes::Far].normal.y      = mat[1][3] - mat[1][2];
    m_Planes[Planes::Far].normal.z      = mat[2][3] - mat[2][2];
    m_Planes[Planes::Far].m_DistanceToOrigin      = mat[3][3] - mat[3][2];

    for (auto& plane : m_Planes)
    {
        float length             =  glm::length(plane.normal);
        plane.normal            /= length;
        plane.m_DistanceToOrigin  /= length;
    }
}

bool ViewFrustum::IsInFrustum(const Entity& element) const{
    for(Plane plane: m_Planes){
        if(plane.DistanceToPoint(element.GetVP(plane.normal)) < 0){
            return false;
        }
    }
    return true;
}