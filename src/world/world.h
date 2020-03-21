#pragma once

#include <unordered_map>
#include "maths/vector.h"
#include "renderer/renderer.h"
#include "chunk/superchunk.h"
#include "chunk/chunk-manager.h"
#include "world/player.h"
#include <pthread.h>
#include <unistd.h>

class World{
public:
    static void Generate(Renderer &renderer, Camera &camera);
    static World* GetInstance(Camera &camera);
    void Render(Renderer& renderer, Camera &camera);
    void LoadChunks(Camera &camera);
    void Update(Camera& camera);
    Block GetBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z, BlockType type, bool focus = false);
    void FocusBlock(int x, int y, int z, BlockType type);
    Vector2i GetBlockXZ(int x, int z);
    Vector2i GetChunkXZ(int x, int z);
    SuperChunk& GetChunkByBlock(int x, int y, int z);
    void SetSpawnPoint();
    void UpdateChunk(int blockX, int blockY, int blockZ);
    void UnFocusBlock();
    void UpdateFocusBlock(Camera& camera);
    Vector3i GetProjPoint(Camera& camera);
    void Mine(Camera& camera);
    Player m_Player;
    ~World();
private:    
    static World* m_Instance;
    World(Camera &camera);
    void UpdateChunks();
    void UpdatePlayer();
    ChunkManager m_ChunkManager;
    int m_LoadDistance = 2;
    const int m_RenderDistance;
    bool m_Running;
    pthread_t m_LoadChunksThread;
    pthread_mutex_t m_Lock;
    std::unordered_map<Vector3i, Chunk&> m_UpdateChunks;
    Vector3i m_FocusBlock;
};