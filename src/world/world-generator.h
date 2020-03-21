#pragma once
#include <vector>
#include "noise-generator.h"
#include "maths/glm.h"
#include "maths/general.h"
#include "biome/grassland-biome.h"
#include "biome/mountain-biome.h"
#include "utils/random.h"

class SuperChunk;

class WorldGenerator{
public:
    WorldGenerator();
    void GenerateTerrain(SuperChunk& chunk);
    void GenerateClouds(SuperChunk& chunk);
private:
    SuperChunk* m_Chunk = nullptr;
    MountainBiome m_MountainBiome;
    GrassLandBiome m_GrassLandBiome;
    NoiseGenerator m_BiomeNoise;
    NoiseGenerator m_CloudNoise;
    void SetBiomeNoiseParams();
    void SetCloudNoiseParams();
    int m_HeightMap[CHUNK_SIZE][CHUNK_SIZE]; 
    Biome& GetBiome(int x, int z);
    int GetHeightIn(int xMin, int zMin, int xMax, int zMax);
    int GetHeight(int x, int z);
    void GenerateHeightMap();
};