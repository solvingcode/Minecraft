#include "world-generator.h"
#include "chunk/superchunk.h"

namespace
{
const int seed = Random::Get().GetIntInRange(500, 500000);
}

WorldGenerator::WorldGenerator()
    : m_MountainBiome(seed), m_BiomeNoise(seed), m_GrassLandBiome(seed), m_CloudNoise(seed)
{
    SetBiomeNoiseParams();
    SetCloudNoiseParams();
}

void WorldGenerator::SetBiomeNoiseParams(){
    NoiseParameters params;
    params.m_Octaves        = 6;
    params.m_Amplitude      = 120.0;
    params.m_Persistance    = 0.75;
    params.m_Smoothness     = 1000.0;
    m_BiomeNoise.SetParameters(params);
}

void WorldGenerator::SetCloudNoiseParams(){
    NoiseParameters params;
    params.m_Octaves        = 7;
    params.m_Amplitude      = 40.0;
    params.m_Persistance    = 0.50;
    params.m_Smoothness     = 60;
    m_CloudNoise.SetParameters(params);
}

Biome &WorldGenerator::GetBiome(int x, int z)
{
    double biomeValue = m_BiomeNoise.PerlinNoise(x, z);
    if(biomeValue > 100){
        return m_GrassLandBiome;
    }else{
        return m_MountainBiome;
    }
}


int WorldGenerator::GetHeight(int x, int z)
{
    Biome &biome = GetBiome(x, z);
    int height = biome.GetHeight(x, z);
    return height;
}



int WorldGenerator::GetHeightIn(int xMin, int zMin, int xMax, int zMax)
{
    int xChunk = m_Chunk->m_Position.x;
    int zChunk = m_Chunk->m_Position.z;

    float bottomLeft  = static_cast<float>(GetHeight(xChunk + xMin, zChunk + zMin));
	float bottomRight = static_cast<float>(GetHeight(xChunk + xMax, zChunk + zMin));
	float topLeft     = static_cast<float>(GetHeight(xChunk + xMin, zChunk + zMax));
	float topRight    = static_cast<float>(GetHeight(xChunk + xMax, zChunk + zMax));

    for (int x = xMin; x < xMax; x++)
    for (int z = zMin; z < zMax; z++)
    {
        if (x == CHUNK_SIZE)
            continue;
        if (z == CHUNK_SIZE)
            continue;

        float h = smoothInterpolation(
			bottomLeft, topLeft, bottomRight, topRight,
			static_cast<float>(xMin), static_cast<float>(xMax),
			static_cast<float>(zMin), static_cast<float>(zMax),
			static_cast<float>(x), static_cast<float>(z));

        m_HeightMap[x][z] = static_cast<int>(h);
    }
}

void WorldGenerator::GenerateHeightMap()
{
    const int part = 2;
    const int PART_SIZE = CHUNK_SIZE / part;
    for(int zPart = 0; zPart < part; zPart ++){
        for(int xPart = 0; xPart < part; xPart ++){
            GetHeightIn(
                xPart * PART_SIZE, 
                zPart * PART_SIZE, 
                (xPart + 1) * PART_SIZE, 
                (zPart + 1) * PART_SIZE
            );
        }
    }
}

void WorldGenerator::GenerateTerrain(SuperChunk &chunk)
{
    m_Chunk = &chunk;

    GenerateHeightMap();

    std::vector<glm::vec3> trees;
    std::vector<glm::vec3> plants;

    for (int x = 0; x < CHUNK_SIZE; x++)
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int height = m_HeightMap[x][z];
            Biome &biome = GetBiome(m_Chunk->m_Position.x + x, m_Chunk->m_Position.z + z);

            int h = std::max(WATER_LEVEL, height);
            for (int y = 0; y <= h; y++)
            {
                if (y <= height)
                {
                    if (y == height)
                    {
                        if (y >= WATER_LEVEL)
                        {
                            if(y < WATER_LEVEL + 2){
                                m_Chunk->SetBlock(x, y, z, biome.GetNearWaterBlock());
                                continue;
                            }
                            if (Random::Get().GetIntInRange(0, biome.GetTreeFreq()) == 2)
                            {
                                trees.emplace_back(x, y + 1, z);
                            }
                            if (Random::Get().GetIntInRange(0, biome.GetPlantFreq()) == 2)
                            {
                                plants.emplace_back(x, y + 1, z);
                            }
                            m_Chunk->SetBlock(x, y, z, biome.GetTopBlock());
                        }
                        else
                        {
                            m_Chunk->SetBlock(x, y, z, biome.GetUnderWaterBlock());
                        }
                    }
                    else
                    {
                        m_Chunk->SetBlock(x, y, z, biome.GetBlockInY(y));
                    }
                }
                else
                {
                    if (y <= WATER_LEVEL)
                    {
                        m_Chunk->SetBlock(x, y, z, BlockType::Water);
                    }
                    else
                    {
                        m_Chunk->SetBlock(x, y, z, BlockType::Air);
                    }
                }
            }
        }

    for (glm::vec3 &plant : plants)
    {
        Biome &biome = GetBiome(m_Chunk->m_Position.x + plant.x, m_Chunk->m_Position.z + plant.z);
        m_Chunk->SetBlock(plant.x, plant.y, plant.z, biome.GetPlant());
    }
    for (glm::vec3 &tree : trees)
    {
        Biome &biome = GetBiome(m_Chunk->m_Position.x + tree.x, m_Chunk->m_Position.z + tree.z);
        biome.MakeTree(*m_Chunk, tree);
    }
    GenerateClouds(chunk);
}

void WorldGenerator::GenerateClouds(SuperChunk &chunk)
{
    m_Chunk = &chunk;

    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        double cloudValue = m_CloudNoise.PerlinNoise(m_Chunk->m_Position.x + x, m_Chunk->m_Position.z + z);
        if (cloudValue > 60)
        {
            m_Chunk->SetBlock(x, SKY_LEVEL, z, BlockType::Cloud);
        }
    }
}