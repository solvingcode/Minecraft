#include "chunk.h"
#include "../world.h"
#include "../block/block-base.h"

Chunk::Chunk(glm::vec3 position, World& world): m_World(&world), Entity(position), m_Meshes(*this){
}

Chunk::Chunk(World& world): Chunk(glm::vec3(0,0,0), world){
}

Chunk::~Chunk(){
}

void Chunk::Draw(Renderer& renderer){
    if(m_hasMesh){
        renderer.DrawChunk(this);
    }
}

bool Chunk::MakeMesh(){
    LogTrace("Making mesh (%d, %d) ...\n", (int)m_Position.x, (int)m_Position.z);
    m_Meshes.m_Solid.DeleteMeshes();
    for(int x=0; x<CHUNK_SIZE; x++){
        for(int y=0; y<CHUNK_SIZE; y++){
            for(int z=0; z<CHUNK_SIZE; z++){
                TryAddBlock(x, y, z);
            }
        }
    }
    m_hasMesh = true;
    m_hasBuffer = false;
    return true;
}

bool Chunk::ShouldAddFace(glm::vec3 adjBlockPosition, glm::vec3 blockPosition){
    Block adjBlock = GetBlock(adjBlockPosition.x, adjBlockPosition.y, adjBlockPosition.z);
    Block block = GetBlock(blockPosition.x, blockPosition.y, blockPosition.z);
    
    if(
        !adjBlock.IsActive() || 
        adjBlock.GetType() == BlockType::Air ||
        (!adjBlock.GetProps().m_IsCollidable && adjBlock.GetType() != block.GetType()) ||
        (adjBlock.GetProps().m_IsOpaque && adjBlock.GetType() != block.GetType())
    ){
        return true;
    }
    return false;
}

void Chunk::TryAddFace(std::array<float, 12>& blockFace, std::array<VectorXY, 4>& texCoords, glm::vec3& position, glm::vec3 AdjacentBlock, float light){
    //@TODO : verify why position.y = 0 is showed (comment this condition to see the problem)
    if(m_Position.y == 0) return;
    /////////////////////////////////////////////////////////////////////////////////////////
    if(ShouldAddFace(AdjacentBlock, position)){
        Block block = GetBlock(position.x, position.y, position.z);
        if(block.GetType() == BlockType::Water){
            m_Meshes.m_Water.AddFace(blockFace, texCoords, position, light);
        }else if(block.GetType() == BlockType::Cloud){
            m_Meshes.m_Cloud.AddFace(blockFace, texCoords, position, light);
        }else{
            m_Meshes.m_Solid.AddFace(blockFace, texCoords, position, light);
        }
    }
}

void Chunk::TryAddBlock(int x, int y, int z){
    
    Block block = GetBlock(x, y, z);
    if(!block.IsActive() || block.GetType() == BlockType::Air){
        return;
    }

    std::array<float, 12> frontFace = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };
    std::array<float, 12> backFace = {
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f
    };
    std::array<float, 12> leftFace = {
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f
    };
    std::array<float, 12> rightFace = {
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f
    };
    std::array<float, 12> bottomFace = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f
    };
    std::array<float, 12> topFace = {
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f
    };
    std::array<float, 12> xFace1 = {
        -0.5f,  -0.5f, -0.5f,
        0.5f,  -0.5f, 0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  -0.5f
    };
    std::array<float, 12> xFace2 = {
        -0.5f,  -0.5f, 0.5f,
        0.5f,  -0.5f, -0.5f, 
        0.5f,  0.5f,  -0.5f, 
        -0.5f,  0.5f,  0.5f
    };
    std::array<float, 12> xFace3 = {
        0.0f,  -0.5f, -0.5f,
        0.0f,  -0.5f, 0.5f, 
        0.0f,  0.5f,  0.5f, 
        0.0f,  0.5f,  -0.5f
    };
    std::array<float, 12> xFace4 = {
        -0.5f,  -0.5f, 0.0f,
        0.5f,  -0.5f, 0.0f, 
        0.5f,  0.5f,  0.0f, 
        -0.5f,  0.5f, 0.0f
    };

    float LIGHT_TOP = 1.0f;
    float LIGHT_X = 0.8f;
    float LIGHT_Z = 0.6f;
    float LIGHT_BOTTOM = 0.4f;

    //@TODO : this is temporary, improve selection blocks
    if(block.IsFocus()){
        LIGHT_TOP = 1.2f;
        LIGHT_X = 1.2f;
        LIGHT_Z = 1.2f;
        LIGHT_BOTTOM = 1.2f;
    }

    glm::vec3 position = {x, y, z};
    BlockTex texCoords = block.GetProps().m_TexCoords;

    if(block.GetProps().m_MeshType == BlockMeshType::X){
        m_Meshes.m_Solid.AddFace(xFace1, texCoords.top, position, LIGHT_X);
        m_Meshes.m_Solid.AddFace(xFace2, texCoords.top, position, LIGHT_X);
        return;
    }

    if(block.GetProps().m_MeshType == BlockMeshType::Star){
        m_Meshes.m_Solid.AddFace(xFace1, texCoords.top, position, LIGHT_X);
        m_Meshes.m_Solid.AddFace(xFace2, texCoords.top, position, LIGHT_X);
        m_Meshes.m_Solid.AddFace(xFace3, texCoords.top, position, LIGHT_X);
        m_Meshes.m_Solid.AddFace(xFace4, texCoords.top, position, LIGHT_X);
        return;
    }

    TryAddFace(frontFace, texCoords.front, position, {x, y, z-1}, LIGHT_Z);
    TryAddFace(backFace, texCoords.back, position, {x, y, z+1}, LIGHT_Z);
    TryAddFace(leftFace, texCoords.left, position, {x-1, y, z}, LIGHT_X);
    TryAddFace(rightFace, texCoords.right, position, {x+1, y, z}, LIGHT_X);
    if(m_Position.y != 0 || y != 0)
        TryAddFace(bottomFace, texCoords.bottom, position, {x, y-1, z}, LIGHT_BOTTOM);
    TryAddFace(topFace, texCoords.top, position, {x, y+1, z}, LIGHT_TOP);

}

void Chunk::UpdateVBO(){
    if(m_hasBuffer) return;
    m_Meshes.m_Solid.UpdateVBO();
    m_Meshes.m_Water.UpdateVBO();
    m_Meshes.m_Cloud.UpdateVBO();
    m_hasBuffer = true;
}

bool Chunk::HasMesh(){
    return m_hasMesh;
}

bool Chunk::HasBuffer(){
    return m_hasBuffer;
}

Block Chunk::GetBlock(int x, int y, int z) const{
    if(OutOfBounds(x, y, z)){
        glm::vec3 position = ToWorldPosition(x, y, z);
        Block block = m_World->GetBlock(position.x, position.y, position.z);
        return block;
    }else{
        return m_Blocks[GetBlockIndex(x,y,z)];
    }
}

Block Chunk::GetChunkBlock(int x, int y, int z) const{
    if(OutOfBounds(x, y, z)){
        return Block(BlockType::Air);
    }else{
        return m_Blocks[GetBlockIndex(x,y,z)];
    }
}

glm::vec3 Chunk::ToWorldPosition(int x, int y, int z) const{
    return {
        m_Position.x + x,
        m_Position.y + y,
        m_Position.z + z
    };
}

bool Chunk::OutOfBounds(int x, int y, int z) const{
    return OutOfBounds(x) || OutOfBounds(y) || OutOfBounds(z); 
}

bool Chunk::OutOfBounds(int value) const{
    return value < 0 || value >= CHUNK_SIZE; 
}

void Chunk::SetBlock(int x, int y, int z, BlockType type, bool focus){
    if(OutOfBounds(x) || OutOfBounds(y) || OutOfBounds(z)){
        return;
    }
    Block& b = m_Blocks[GetBlockIndex(x,y,z)];
    b.SetBlockType(type);
    b.SetFocus(focus);
}

int Chunk::GetBlockIndex(int x, int y, int z) const{
    return y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x;
}

void Chunk::DeleteMeshes(){
    m_hasMesh = false;
    m_Meshes.m_Solid.DeleteMeshes();
}

MeshCollection& Chunk::GetMeshes(){
    return m_Meshes;
}