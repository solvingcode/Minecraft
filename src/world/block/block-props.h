#pragma once
#include "maths/vector.h"
#include <array>
#include "block-type.h"

struct BlockTex{
    std::array<VectorXY, 4> front;
    std::array<VectorXY, 4> back;
    std::array<VectorXY, 4> left;
    std::array<VectorXY, 4> right;
    std::array<VectorXY, 4> bottom;
    std::array<VectorXY, 4> top;
};

enum BlockMeshType{
    Cube,
    X,
    Star
};

struct BlockProps{
    BlockProps(const std::string block);
    BlockTex m_TexCoords;
    bool m_IsCollidable = false;  
    bool m_IsOpaque = true;
    BlockMeshType m_MeshType;
};