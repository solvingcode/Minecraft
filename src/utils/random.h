#pragma once
#include <random>

class Random{
public:
    static Random& Get();
    void SetSeed(int seed);
    int GetIntInRange(int min, int max);
private:
    Random();
    std::mt19937 m_Random;
};