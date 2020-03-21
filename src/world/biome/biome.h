#pragma once
#include "../noise-generator.h"
#include "maths/glm.h"
#include "../block/block-type.h"
#include "utils/random.h"

class SuperChunk;

class Biome{
public:
    Biome(NoiseParameters noiseParam, int treeFreq, int plantFreq, int seed);
    int GetHeight(int x, int z);
    int GetTreeFreq();
    int GetPlantFreq();
    virtual void MakeTree(SuperChunk& chunk, glm::vec3 tree) = 0;
    virtual BlockType GetTopBlock() = 0;
    virtual BlockType GetUnderWaterBlock() = 0;
    virtual BlockType GetNearWaterBlock() = 0;
    virtual BlockType GetPlant() = 0;
    virtual BlockType GetBlockInY(int y) = 0;
protected:
    virtual NoiseParameters GetNoiseParameters() = 0;
private:
    NoiseGenerator m_NoiseGenerator;
    int m_TreeFreq;
    int m_PlantFreq;
};