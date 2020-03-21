#pragma once

#include <cmath>
#include "utils/constants.h"
#include <iostream>

struct NoiseParameters{
    int m_Octaves, m_HeightOffset; 
    double m_Frequency, m_Amplitude, m_Persistance, m_Smoothness, m_Roughness, m_Scale;
};

class NoiseGenerator{
public:
    NoiseGenerator(int seed);
    NoiseGenerator(NoiseParameters& noiseParam, int seed);
    double Noise(double x, double z);
    double GetNoise(int t);
    double GetNoise(double x, double z);
    double CosineInterpolate(double a, double b, double t);
    double PerlinNoise(double x, double z);
    void SetParameters(NoiseParameters& noiseParam);
    NoiseParameters GetNoiseParameters();
private:
    int m_Seed;
    NoiseParameters m_NoiseParameters;
};  