#include "random.h"

Random& Random::Get(){
    static Random r;
    return r;
}

void Random::SetSeed(int seed){
    m_Random.seed(seed);
}

Random::Random(){
    m_Random.seed(time(NULL));
}

int Random::GetIntInRange(int min, int max){
    auto dist = std::uniform_int_distribution<int>(min,max);
    return dist(m_Random);
}