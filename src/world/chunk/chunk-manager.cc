#include "chunk-manager.h"

ChunkManager::ChunkManager(World* world): m_World(world){
}

ChunkManager::~ChunkManager(){
}

ChunkMap& ChunkManager::GetChunks(){
    return m_Chunks;
}

bool ChunkManager::MakeMesh(Camera& camera, int x, int z){
    SuperChunk& chunk = GetChunk(x, z);
    return chunk.MakeMesh(camera);
}

bool ChunkManager::LoadMesh(int x, int z){
    SuperChunk& chunk = GetChunk(x, z);
    chunk.Load(m_WorldGenerator);
    return true;
}

void ChunkManager::DeleteMeshes(){
    for(auto& chunk : m_Chunks){
        chunk.second.DeleteMeshes();
    }
}

SuperChunk& ChunkManager::GetChunk(int x, int z){
    Vector2i key {x, z};
    if(!ChunkExistsAt(x, z)){
        LogTrace("Creating mesh (%d, %d)...\n", x, z);
        SuperChunk chunk(glm::vec3(x, 0, z), *m_World);
        m_Chunks.emplace(key, std::move(chunk));
    }

    return m_Chunks[key];
}

SuperChunk* ChunkManager::GetChunkIfExists(int x, int z){
    Vector2i key {x, z};
    if(!ChunkExistsAt(x, z)){
        return nullptr;
    }
    return &m_Chunks[key];
}

bool ChunkManager::ChunkExistsAt(int x, int z){
    Vector2i key {x, z};
    return m_Chunks.find(key) != m_Chunks.end();
}

void ChunkManager::UnLoadChunk(int x, int z){
    if(ChunkExistsAt(x, z))
        m_Chunks.erase({x, z});
}