#pragma once
#include <vector>
#include "../world-generator.h"
#include "chunk.h"

class SuperChunk : public Entity {
public:
    SuperChunk() = default;
    SuperChunk(glm::vec3 position, World& world): m_World(&world), Entity(position) {}
    ~SuperChunk() = default;
    bool MakeMesh(Camera& camera);
    void SetBlock(int x, int y, int z, BlockType type, bool focus = false);
    Block GetBlock(int x, int y, int z);
    bool OutOfBounds(int x, int y, int z);
    void Draw(Renderer &renderer, Camera& camera);
    bool IsLoaded();
    void Load(WorldGenerator& generator);
    Chunk& GetChunk(int index);
    void AddChunk();
    void AddChunkIndex(int index);
    void DeleteMeshes();
    void UpdateVBO();
    int GetTopBlockAt(int x, int z);
private:
    std::vector<Chunk> m_Chunks;
    bool m_Loaded = false;
    World* m_World;
    std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE> m_TopBlocks = {};
};