#pragma once
#include "world/block/block.h"
#include "vertex/vertex-array.h"
#include "vertex/index-buffer.h"
#include "core/entity.h"
#include "renderer/renderer.h"
#include "utils/constants.h"
#include <array>
#include "maths/vector.h"
#include "mesh.h"

class World;
class Renderer;
class Camera;

struct MeshCollection{
    MeshCollection(Entity& entity): m_Solid(entity), m_Water(entity), m_Cloud(entity){}
    Mesh m_Solid;
    Mesh m_Water;
    Mesh m_Cloud;
};

class Chunk : public Entity{
public:
    Chunk(World& world);
    Chunk(glm::vec3 position, World& world);
    Chunk() = default;
    ~Chunk();

    Block GetBlock(int x, int y, int z) const;
    Block GetChunkBlock(int x, int y, int z) const;
    bool MakeMesh();
    void TryAddBlock(int x, int y, int z);
    void TryAddFace(std::array<float, 12>& blockFace, std::array<VectorXY, 4>& texCoords, glm::vec3& position, glm::vec3 AdjacentBlock, float light);
    bool ShouldAddFace(glm::vec3 adjBlockPosition, glm::vec3 blockPosition);

    void UpdateVBO();
    bool HasMesh();
    bool HasBuffer();
    void SetBlock(int x, int y, int z, BlockType type, bool focus = false);
    bool OutOfBounds(int value) const;
    bool OutOfBounds(int x, int y, int z) const;
    void Draw(Renderer& renderer);
    int GetBlockIndex(int x, int y, int z) const;
    glm::vec3 ToWorldPosition(int x, int y, int z) const;
    void DeleteMeshes();
    MeshCollection& GetMeshes();

private:
    Block m_Blocks[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE];
    bool m_Loaded = false;
    bool m_hasMesh = false;
    bool m_hasBuffer = false;
    World *m_World;
    MeshCollection m_Meshes;
};