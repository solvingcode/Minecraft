#include "grassland-biome.h"
#include "../chunk/superchunk.h"

GrassLandBiome::GrassLandBiome(int seed): Biome(GetNoiseParameters(), 100, 2, seed){
}

NoiseParameters GrassLandBiome::GetNoiseParameters(){
    NoiseParameters params;
    params.m_Octaves       = 7;
    params.m_Amplitude     = 40.0;
    params.m_Persistance   = 0.50;
    params.m_Smoothness = 60;
    return params;
}

void GrassLandBiome::MakeTree(SuperChunk& chunk, glm::vec3 tree){
    Tree::GenerateOak(chunk, tree);
}

BlockType GrassLandBiome::GetTopBlock(){
    return BlockType::Grass;
}

BlockType GrassLandBiome::GetPlant(){
    return Random::Get().GetIntInRange(0,10) > 1 ? BlockType::Plant : BlockType::FlowerYellow;
}

BlockType GrassLandBiome::GetUnderWaterBlock(){
    return Random::Get().GetIntInRange(0,10) > 2 ? BlockType::Sand : BlockType::Stone;
}

BlockType GrassLandBiome::GetNearWaterBlock(){
    return BlockType::Sand;
}

BlockType GrassLandBiome::GetBlockInY(int y){
    return BlockType::Dirt;
}