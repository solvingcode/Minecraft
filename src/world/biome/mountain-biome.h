#pragma once
#include "biome.h"
#include "world/environnement/tree.h"

class MountainBiome : public Biome{
public:
    MountainBiome(int seed);
    void MakeTree(SuperChunk& chunk, glm::vec3 tree) override;
    BlockType GetTopBlock() override;
    BlockType GetUnderWaterBlock() override;
    BlockType GetNearWaterBlock() override;
    BlockType GetPlant() override;
    BlockType GetBlockInY(int y) override;
private:
    NoiseParameters GetNoiseParameters() override;
};