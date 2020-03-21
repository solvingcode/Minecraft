#include "player.h"
#include "world.h"
#include "core/window.h"

Player::Player()
: Entity(glm::vec3(2100.0f, 100.0f, 2100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.02f)
, m_Acceleration(glm::vec3(0)){
}

void Player::Update(World& world){
    m_Velocity += m_Acceleration;
    m_Acceleration = {0,0,0};
    float gravity;

    if(m_IsUnderWater){
        gravity = 0.0001f;
        m_Speed = 0.005f;
    }else{
        gravity = 0.02f;
        m_Speed = 0.02f;
    }

    if(!m_IsFly){
        if(!m_OnGround){
            m_Velocity.y -= gravity * 1;
        }
        m_OnGround = false;
    }

    if(!m_IsFly){
        Collide(world, {m_Velocity.x, 0, 0});
        Collide(world, {0, m_Velocity.y, 0});
        Collide(world, {0, 0, m_Velocity.z});
    }

    m_Position += m_Velocity;
    m_Velocity.x *= 0.65f;
    m_Velocity.z *= 0.65f;
    if(m_IsFly){
        m_Velocity.y *= 0.65f;
    }

    if(m_OnGround){
        m_Position.y = floor(m_Position.y);
    }
}

bool Player::IsUnderWater(){
    return m_IsUnderWater;
}

void Player::SetUnderWater(bool underwater){
    m_IsUnderWater = underwater;
}

void Player::Collide(World& world, glm::vec3 velocity){
    glm::vec3 dimensions = {0.7f, 0.8f, 0.7f};
    glm::vec3 newPosition = m_Position + velocity;
    for(int x = newPosition.x; x <= newPosition.x + dimensions.x; x++)
    for(int y = newPosition.y - 1.0f; y <= newPosition.y + dimensions.y; y++)
    for(int z = newPosition.z; z <= newPosition.z + dimensions.z; z++)
    {
        Block block = world.GetBlock(x, y, z);
        if(block.GetType() != BlockType::Air && block.GetProps().m_IsCollidable){
            if(velocity.y > 0){
                m_Velocity.y = 0;
            }else if(velocity.y < 0){
                m_Velocity.y = 0;
                m_OnGround = true;
            }
            if(velocity.x != 0){
                m_Velocity.x = 0;
            }
            if(velocity.z != 0){
                m_Velocity.z = 0;
            }
        }
    }
}

void Player::Jump(){
    if(m_IsUnderWater){
        m_Acceleration.y += 0.001f;
    }
    else if(m_OnGround){
        m_OnGround = false;
        m_Acceleration.y += (m_Speed*1.5f) * 10;
    }
}

void Player::Move(glm::vec3 direction){
    m_Acceleration = GetAcceleration(direction);
}

void Player::HandleInput(Window& window){
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_W)){
        Move({0.f, 0.f, -1.f});
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_S)){
        if(m_IsUnderWater) Move({0.f, -1.f, 0.f});
        else Move({0.f, 0.f, 1.f});
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_A)){
        Move({-1.f, 0.f, 0.f});
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_D)){
        Move({1.f, 0.f, 0.f});
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_SPACE)){
        Jump();
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_LEFT_CONTROL)){
        if(!m_IsFly){
            m_IsFly = true;
            m_Speed *= 4;
        }
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_RIGHT_CONTROL)){
        if(m_IsFly){
            m_IsFly = false;
            m_Speed /= 4;
        }
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_LEFT_SHIFT)){
        m_Acceleration.y += m_Speed;
    }
    if(window.m_Keyboard.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT)){
        m_Acceleration.y -= m_Speed;
    }
}

Player::~Player(){
    LogTrace("Destructing player...\n");
}