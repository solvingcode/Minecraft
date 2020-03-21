#include "biome.h"

Biome::Biome(NoiseParameters noiseParam, int treeFreq, int plantFreq, int seed)
: m_TreeFreq(treeFreq)
, m_PlantFreq(plantFreq)
, m_NoiseGenerator(noiseParam, seed){
}

int Biome::GetHeight(int x, int z){
    return m_NoiseGenerator.PerlinNoise(x, z);
}

int Biome::GetTreeFreq(){
    return m_TreeFreq;
}

int Biome::GetPlantFreq(){
    return m_PlantFreq;
}