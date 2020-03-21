#include "superchunk.h"

bool SuperChunk::MakeMesh(Camera& camera)
{
    for (Chunk &chunk : m_Chunks)
    {
        if (
            !chunk.HasMesh() 
            && camera.GetViewFrustum().IsInFrustum(chunk)
        )
        {
            chunk.MakeMesh();
            return true;
        }
    }
    return false;
}

void SuperChunk::SetBlock(int x, int y, int z, BlockType type, bool focus)
{
    int index = y / CHUNK_SIZE;
    AddChunkIndex(index);

    if(OutOfBounds(x,y,z)){
        return;
    }

    m_Chunks[index].SetBlock(x,y % CHUNK_SIZE,z, type, focus);

    if(type != BlockType::Air){
        BlockProps props = BlockBase::Get()->GetBlockProps(type);

        if(y > m_TopBlocks[x][z] && props.m_IsCollidable){
            m_TopBlocks[x][z] = y;
        }
    }
}

int SuperChunk::GetTopBlockAt(int x, int z){
    return m_TopBlocks[x][z];
}

Block SuperChunk::GetBlock(int x, int y, int z){
    if(OutOfBounds(x, y, z)){
        return BlockType::Air;
    }

    return m_Chunks[y / CHUNK_SIZE].GetBlock(x, y % CHUNK_SIZE, z);
}

bool SuperChunk::OutOfBounds(int x, int y, int z){
    if(
        x >= CHUNK_SIZE || 
        z >= CHUNK_SIZE ||
        x < 0 ||
        y < 0 ||
        z < 0 ||
        y >= (int)m_Chunks.size() * CHUNK_SIZE
    ){
        return true;
    }
    return false;
}

void SuperChunk::Draw(Renderer &renderer, Camera& camera){
    for(Chunk &chunk : m_Chunks){
        if(camera.GetViewFrustum().IsInFrustum(chunk))
        chunk.Draw(renderer);
    }
}

bool SuperChunk::IsLoaded(){
    return m_Loaded;
}

void SuperChunk::Load(WorldGenerator& generator){
    if(IsLoaded()){
        return;
    }
    
    generator.GenerateTerrain(*this);

    m_Loaded = true;
}

Chunk& SuperChunk::GetChunk(int index){
    if(index >= (int)m_Chunks.size() || index < 0){
        printf("Error getting chunk outside range! (size : %d)\n", (int)m_Chunks.size());
        exit(EXIT_FAILURE);
    }

    return m_Chunks[index];
}

void SuperChunk::AddChunk(){
    int y = (int)m_Chunks.size();
    m_Chunks.emplace_back(glm::vec3(m_Position.x, y * CHUNK_SIZE, m_Position.z), *m_World);
}

void SuperChunk::AddChunkIndex(int index){
    while ((int)m_Chunks.size() <= index)
    {
        AddChunk();
    }
}

void SuperChunk::DeleteMeshes(){
    for(Chunk& chunk : m_Chunks){
        chunk.DeleteMeshes();
    }
}

void SuperChunk::UpdateVBO(){
    for(Chunk& chunk : m_Chunks){
        chunk.UpdateVBO();
    }
}