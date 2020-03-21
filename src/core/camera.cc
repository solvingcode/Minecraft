#include "camera.h"

Camera::Camera(float fov, float znear, float zfar) 
: m_Fov(fov)
, m_Znear(znear)
, m_Zfar(zfar)
{
}

Camera::~Camera() {
    LogTrace("Destructing camera...\n");
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 matrix(1.f);

    matrix = glm::rotate(matrix, glm::radians(m_Rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, -m_Position);

    return matrix;
}

glm::mat4 Camera::GetViewMatrixRotation()
{
    glm::mat4 matrix(1.f);

    matrix = glm::rotate(matrix, glm::radians(m_Rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(m_Rotation.z), {0, 0, 1});

    return matrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    int windowX = SCREEN_WIDTH;
    int windowY = SCREEN_HEIGHT;
    float screenWidth = (float)windowX;
    float screenHeight = (float)windowY;
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(m_Fov), screenWidth / screenHeight, m_Znear, m_Zfar);

    return projection;
}

void Camera::Update(Player &player){
    Camera::UpdateGeoInfo(player);
    m_ViewFrustum.Update(GetProjectionMatrix() * GetViewMatrix());
}

glm::vec3 Camera::GetRay(){
    glm::mat4 proj = GetProjectionMatrix();
    glm::mat4 view = GetViewMatrixRotation();

    glm::mat4 inVP = glm::inverse(proj * view);
    glm::vec4 screenPos = glm::vec4(0.f, 0.0f, 0.0f, 1.0f);
    glm::vec4 worldPos = inVP * screenPos;

    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

    return dir;
}

void Camera::UpdateGeoInfo(Player &player){
    m_Position = player.m_Position;
    m_Rotation = player.m_Rotation;
    m_Velocity = player.m_Velocity;
}

const ViewFrustum& Camera::GetViewFrustum() const {
    return m_ViewFrustum;
}