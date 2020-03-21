#pragma once
#include <unordered_map>
#include <vector>
#include "maths/vector.h"
#include "superchunk.h"
#include "world/world-generator.h"

class World;

using ChunkMap = std::unordered_map<Vector2i, SuperChunk>;

class ChunkManager
{
public:
    ChunkManager(World *world);
    ~ChunkManager();
    ChunkMap &GetChunks();
    SuperChunk& GetChunk(int x, int z);
    SuperChunk* GetChunkIfExists(int x, int z);
    bool MakeMesh(Camera& camera, int x, int z);
    bool LoadMesh(int x, int z);
    bool ChunkExistsAt(int x, int z);
    void DeleteMeshes();
    void UnLoadChunk(int x, int z);

private:
    ChunkMap m_Chunks;
    World* m_World;
    WorldGenerator m_WorldGenerator;
};