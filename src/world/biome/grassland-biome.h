#pragma once
#include "biome.h"
#include "world/environnement/tree.h"

class GrassLandBiome : public Biome{
public:
    GrassLandBiome(int seed);
    void MakeTree(SuperChunk& chunk, glm::vec3 tree) override;
    BlockType GetTopBlock() override;
    BlockType GetUnderWaterBlock() override;
    BlockType GetNearWaterBlock() override;
    BlockType GetPlant() override;
    BlockType GetBlockInY(int y) override;
private:
    NoiseParameters GetNoiseParameters() override;
};