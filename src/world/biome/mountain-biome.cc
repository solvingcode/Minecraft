#include "mountain-biome.h"
#include "../chunk/superchunk.h"

MountainBiome::MountainBiome(int seed): Biome(GetNoiseParameters(), 300, 5, seed){
}

NoiseParameters MountainBiome::GetNoiseParameters(){
    NoiseParameters params;
    params.m_Octaves       = 9;
    params.m_Amplitude     = 83.0;
    params.m_Persistance   = 0.51;
    params.m_Smoothness = 235;
    return params;
}

void MountainBiome::MakeTree(SuperChunk& chunk, glm::vec3 tree){
    Tree::GenerateOak(chunk, tree);
}

BlockType MountainBiome::GetTopBlock(){
    return BlockType::Grass;
}

BlockType MountainBiome::GetPlant(){
    return Random::Get().GetIntInRange(0,10) > 2 ? BlockType::Plant : BlockType::FlowerYellow;
}

BlockType MountainBiome::GetUnderWaterBlock(){
    return Random::Get().GetIntInRange(0,10) > 2 ? BlockType::Sand : BlockType::Stone;
}

BlockType MountainBiome::GetNearWaterBlock(){
    return Random::Get().GetIntInRange(0,10) > 5 ? BlockType::Dirt : BlockType::Sand;
}

BlockType MountainBiome::GetBlockInY(int y){
    int maxRange = 10;
    int conditionRange = 100 - y;
    return Random::Get().GetIntInRange(0,maxRange) > conditionRange ? BlockType::Dirt : BlockType::Stone;
}