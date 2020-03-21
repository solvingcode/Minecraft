#include "noise-generator.h"

NoiseGenerator::NoiseGenerator(int seed): m_Seed(seed){
    m_NoiseParameters.m_Octaves       = 8;
    m_NoiseParameters.m_Amplitude     = 20.0;
    m_NoiseParameters.m_Persistance   = 0.77;
    m_NoiseParameters.m_Smoothness = 100.0;
};

NoiseGenerator::NoiseGenerator(NoiseParameters& noiseParam, int seed): m_Seed(seed), m_NoiseParameters(noiseParam){
};

void NoiseGenerator::SetParameters(NoiseParameters& noiseParam){
    m_NoiseParameters = noiseParam;
}

NoiseParameters NoiseGenerator::GetNoiseParameters(){
    return m_NoiseParameters;
}

double NoiseGenerator::Noise(double x, double z)
{
    int integerX = (int)x;
    int integerZ = (int)z;

    double fractionalX = x - integerX;
    double fractionalZ = z - integerZ;

    double a = GetNoise(integerX, integerZ);
    double b = GetNoise(integerX + 1, integerZ);

    double c = GetNoise(integerX, integerZ + 1);
    double d = GetNoise(integerX + 1, integerZ + 1);

    double f = CosineInterpolate(a, b, fractionalX);
    double g = CosineInterpolate(c, d, fractionalX);

    double result = CosineInterpolate(f, g, fractionalZ);
    return result;
}

double NoiseGenerator::GetNoise(int t)
{
    t += m_Seed;
    t = (t << 13) ^ t;
    t = (t * (t * t * 15731 + 789221) + 1376312589);
    return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

double NoiseGenerator::GetNoise(double x, double z)
{
    return GetNoise(x + z * CHUNK_SIZE);
}

double NoiseGenerator::CosineInterpolate(double a, double b, double t)
{
    double c = (1 - std::cos(t * 3.1415927)) * .5;

    return (1. - c) * a + c * b;
}

double NoiseGenerator::PerlinNoise(double x, double z){
    double r = 0.0;
    for(int i = 0; i < m_NoiseParameters.m_Octaves; i++){
        auto frequency = pow(2.0, i);
        auto amplitude = pow(m_NoiseParameters.m_Persistance, i);
        r += Noise(x*frequency/m_NoiseParameters.m_Smoothness, z*frequency/m_NoiseParameters.m_Smoothness) * amplitude;
    }
    auto result =
            (((r / 2.1) + 1.2) * m_NoiseParameters.m_Amplitude);
    return result > 0 ? result : 1;
}