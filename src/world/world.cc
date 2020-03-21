#include "world.h"

World* World::m_Instance = nullptr;

World* World::GetInstance(Camera &camera){
    if(World::m_Instance == nullptr){
        World::m_Instance = new World(camera);
    }
    return World::m_Instance;
}

void World::Render(Renderer& renderer, Camera& camera){
    pthread_mutex_lock(&m_Lock);
    ChunkMap &chunks = m_ChunkManager.GetChunks();
    //LogTrace("Rendering chunks (%lu)...\n", chunks.size());
    for(auto it = chunks.begin(); it != chunks.end();){
        SuperChunk& chunk = it->second;
        int cameraX = camera.m_Position.x;
        int cameraZ = camera.m_Position.z;

        int minX = cameraX - m_RenderDistance * CHUNK_SIZE;
        int maxX = cameraX + m_RenderDistance * CHUNK_SIZE;
        int minZ = cameraZ - m_RenderDistance * CHUNK_SIZE;
        int maxZ = cameraZ + m_RenderDistance * CHUNK_SIZE;

        auto position = chunk.m_Position;

        if(minX > position.x || maxX < position.x || minZ > position.z || maxZ < position.z){
            it = chunks.erase(it);
            //it++;
            continue;
        }else{
            chunk.Draw(renderer, camera);
            it++;
        }
    }
    pthread_mutex_unlock(&m_Lock);
    //LogTrace("Finish Rendering chunks...\n");
}

void World::SetSpawnPoint(){
    int tries = 0;
    int chunkX = -1;
    int chunkZ = -1;
    int blockX = 0;
    int blockY = 0;
    int blockZ = 0;

    LogTrace("Searching spawn point...\n");

    while(blockY <= WATER_LEVEL){
        m_ChunkManager.UnLoadChunk(chunkX, chunkZ);
        chunkX = Random::Get().GetIntInRange(200, 1000) * CHUNK_SIZE;
        chunkZ = Random::Get().GetIntInRange(200, 1000) * CHUNK_SIZE;
        blockX = Random::Get().GetIntInRange(0, 15);
        blockZ = Random::Get().GetIntInRange(0, 15);

        m_ChunkManager.LoadMesh(chunkX, chunkZ);

        blockY = m_ChunkManager.GetChunk(chunkX, chunkZ).GetTopBlockAt(blockX, blockZ);
        tries++;
    }
    
    int worldX = chunkX + blockX;
    int worldZ = chunkZ + blockZ;

    m_Player.m_Position = {worldX, blockY + 2, worldZ};
    LogTrace("Spawn point founded at (%d, %d, %d) in %d tries...\n", worldX, blockY, worldZ, tries);
}

void World::SetBlock(int x, int y, int z, BlockType type, bool focus){
    if(y >= 0){
        Vector2i blockPosition = GetBlockXZ(x, z);
        Vector2i chunkPosition = GetChunkXZ(x, z);
        m_ChunkManager.GetChunk(chunkPosition.x * CHUNK_SIZE, chunkPosition.z * CHUNK_SIZE).SetBlock(blockPosition.x, y, blockPosition.z, type, focus);
    }
}

void World::FocusBlock(int x, int y, int z, BlockType type){
    UnFocusBlock();
    if(y >= 0){
        SetBlock(x, y, z, type, true);
        m_FocusBlock = Vector3i(x, y, z);
    }
}

void World::UnFocusBlock(){
    if(m_FocusBlock == Vector3i(0,0,0)) return;
    Block focusBlock = GetBlock(m_FocusBlock.x, m_FocusBlock.y, m_FocusBlock.z);
    SetBlock(m_FocusBlock.x, m_FocusBlock.y, m_FocusBlock.z, focusBlock.GetType(), false);
    UpdateChunk(m_FocusBlock.x, m_FocusBlock.y, m_FocusBlock.z);
    m_FocusBlock = Vector3i(0,0,0);
}

void World::Update(Camera& camera){
    UpdateChunks();
    UpdatePlayer();
    UpdateFocusBlock(camera);
}

void World::UpdatePlayer(){
    glm::vec3 position = m_Player.m_Position;
    Block block = GetBlock(position.x, position.y + 0.5f, position.z);
    if(block.GetType() == BlockType::Water){
        m_Player.SetUnderWater(true);
    }else{
        m_Player.SetUnderWater(false);
    }
}

void World::UpdateChunk(int blockX, int blockY, int blockZ){
    pthread_mutex_lock(&m_Lock);
    Vector2i chunkPosition = GetChunkXZ(blockX, blockZ);
    int chunkY = blockY / CHUNK_SIZE;
    Vector3i key(chunkPosition.x * CHUNK_SIZE, chunkY, chunkPosition.z * CHUNK_SIZE);
    m_UpdateChunks.emplace(key, m_ChunkManager.GetChunk(key.x, key.z).GetChunk(key.y));

    Vector2i chunkBlockPosition = GetBlockXZ(blockX, blockZ);
    int chunkBlockY = blockY % CHUNK_SIZE;
    
    if(chunkBlockPosition.x == 0){
        Vector3i newKey((chunkPosition.x - 1) * CHUNK_SIZE, chunkY, chunkPosition.z * CHUNK_SIZE);
        m_UpdateChunks.emplace(newKey, m_ChunkManager.GetChunk(newKey.x, newKey.z).GetChunk(newKey.y));
    }
    
    if(chunkBlockPosition.x == CHUNK_SIZE - 1){
        Vector3i newKey((chunkPosition.x + 1) * CHUNK_SIZE, chunkY, chunkPosition.z * CHUNK_SIZE);
        m_UpdateChunks.emplace(newKey, m_ChunkManager.GetChunk(newKey.x, newKey.z).GetChunk(chunkY));
    }

    if(chunkBlockPosition.z == 0){
        Vector3i newKey(chunkPosition.x * CHUNK_SIZE, chunkY, (chunkPosition.z - 1) * CHUNK_SIZE);
        m_UpdateChunks.emplace(newKey, m_ChunkManager.GetChunk(newKey.x, newKey.z).GetChunk(newKey.y));
    }
    
    if(chunkBlockPosition.z == CHUNK_SIZE - 1){
        Vector3i newKey(chunkPosition.x * CHUNK_SIZE, chunkY, (chunkPosition.z + 1) * CHUNK_SIZE);
        m_UpdateChunks.emplace(newKey, m_ChunkManager.GetChunk(newKey.x, newKey.z).GetChunk(chunkY));
    }

    if(chunkBlockY == 0){
        Vector3i newKey(chunkPosition.x* CHUNK_SIZE, chunkY - 1, chunkPosition.z * CHUNK_SIZE);
        m_UpdateChunks.emplace(newKey, m_ChunkManager.GetChunk(newKey.x, newKey.z).GetChunk(newKey.y));
    }
    
    if(chunkBlockY == CHUNK_SIZE - 1){
        Vector3i newKey(chunkPosition.x * CHUNK_SIZE, chunkY + 1, chunkPosition.z * CHUNK_SIZE);
        m_UpdateChunks.emplace(newKey, m_ChunkManager.GetChunk(newKey.x, newKey.z).GetChunk(chunkY));
    }

    pthread_mutex_unlock(&m_Lock);
}

void World::UpdateChunks(){
    pthread_mutex_lock(&m_Lock);
    for(auto& updateChunk : m_UpdateChunks){
        Chunk& chunk = updateChunk.second;
        chunk.MakeMesh();
    }
    m_UpdateChunks.clear();
    pthread_mutex_unlock(&m_Lock);
}

Block World::GetBlock(int x, int y, int z){
    Vector2i blockPosition = GetBlockXZ(x, z);
    Vector2i chunkPosition = GetChunkXZ(x, z);
    Block block = m_ChunkManager.GetChunk(chunkPosition.x * CHUNK_SIZE, chunkPosition.z * CHUNK_SIZE).GetBlock(blockPosition.x, y, blockPosition.z);
    return block;
}

SuperChunk& World::GetChunkByBlock(int x, int y, int z){
    Vector2i chunkPosition = GetChunkXZ(x, z);
    return m_ChunkManager.GetChunk(chunkPosition.x * CHUNK_SIZE, chunkPosition.z * CHUNK_SIZE);
}

Vector2i World::GetBlockXZ(int x, int z){
    return {
        x % CHUNK_SIZE,
        z % CHUNK_SIZE
    };
}

Vector2i World::GetChunkXZ(int x, int z){
    return {
        x / CHUNK_SIZE,
        z / CHUNK_SIZE
    };
}


Vector3i World::GetProjPoint(Camera& camera){
    glm::vec3 rayStartPosition = camera.m_Position + glm::vec3(0.5f, 0.0f, 0.5f);
    glm::vec3 rayEndPosition = rayStartPosition;
    glm::vec3 ray = camera.GetRay();
    float maxDistance = 2.0f;
    float step = 0.05f;
    float cStep = step;
    while(glm::distance(rayStartPosition, rayEndPosition) < maxDistance){
        rayEndPosition = rayStartPosition + ray * cStep;
        int x = rayEndPosition.x;
        int y = rayEndPosition.y + 0.5f;
        int z = rayEndPosition.z;

        Block block = GetBlock(x, y, z);
        BlockType blockType = block.GetType();
        if(blockType != BlockType::Air && blockType != BlockType::Water){
            return Vector3i(x, y, z);
        }
        cStep += step;
    }
    return Vector3i(0,0,0);
}

void World::Mine(Camera& camera){
    Vector3i point = GetProjPoint(camera);
    if(point == Vector3i(0,0,0)) return;
    UpdateChunk(point.x, point.y, point.z);
    SetBlock(point.x, point.y, point.z, BlockType::Air);
}

void World::UpdateFocusBlock(Camera& camera){
    Vector3i point = GetProjPoint(camera);
    UnFocusBlock();
    if(point == Vector3i(0,0,0)) return;
    BlockType blockType = GetBlock(point.x, point.y, point.z).GetType();
    UpdateChunk(point.x, point.y, point.z);
    FocusBlock(point.x, point.y, point.z, blockType);
}

void World::LoadChunks(Camera& camera){
    while(m_Running){
        int cameraX = camera.m_Position.x/CHUNK_SIZE;
        int cameraZ = camera.m_Position.z/CHUNK_SIZE;
        //LogTrace("Load Chunks (%d, %d, %d)...\n", cameraX, cameraZ, m_LoadDistance);
        bool isMeshMade = false;
        for(int i=0; i < m_LoadDistance; i++){
            int minX = std::max(cameraX - i, 0);
            int minZ = std::max(cameraZ - i, 0);
            int maxX = cameraX + i;
            int maxZ = cameraZ + i;
            for(int x = minX; x<maxX; x++){
                for(int z = minZ; z<maxZ; z++){
                    pthread_mutex_lock(&m_Lock);
                    m_ChunkManager.LoadMesh(x*CHUNK_SIZE, z*CHUNK_SIZE);
                    if(x != minX && x != maxX - 1 && z != minZ && z != maxZ - 1){
                        isMeshMade = m_ChunkManager.MakeMesh(camera, x*CHUNK_SIZE, z*CHUNK_SIZE);
                    }
                    pthread_mutex_unlock(&m_Lock);
                }
            }
            if(isMeshMade){
                break;
            }
        }
        if(!isMeshMade){
            m_LoadDistance++;
        }
        if(m_LoadDistance >= m_RenderDistance){
            m_LoadDistance = 2;
        }
        //LogTrace("Finish Load Chunks (%d, %d)...\n", cameraX, cameraZ);
    }                
}

namespace{
    struct ThreadData{
        World* world;
        Camera& camera;
        ThreadData(World* _world, Camera& _camera): world(_world), camera(_camera){}
    };

    void* LoadChunkThread(void *data){
        ThreadData* dataThread = reinterpret_cast<ThreadData*>(data);
        dataThread->world->LoadChunks(dataThread->camera);
    }
};

World::World(Camera& camera): m_RenderDistance(12), m_ChunkManager(this), m_FocusBlock(0,0,0){
    m_Running = true;
    SetSpawnPoint();
    camera.UpdateGeoInfo(m_Player);

    ThreadData* data = new ThreadData(this, camera);
    usleep(50);
    if(pthread_mutex_init(&m_Lock, NULL) != 0){
        printf("Mutex init failed !\n");
        exit(EXIT_FAILURE);
    }
    pthread_create(&m_LoadChunksThread, NULL, LoadChunkThread, data);
}

World::~World(){
    m_Running = false;
    pthread_join(m_LoadChunksThread, NULL);
    pthread_mutex_destroy(&m_Lock);
}