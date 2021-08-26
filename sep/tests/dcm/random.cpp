#include "random.hpp"
#include <iostream>
Random::Random() : eng_(rd_())
{
    // do nothing
}

Random& Random::GetInstance() 
{
    static Random instance;
    return instance;    
}

float Random::Float() 
{
    return Random::GetInstance().FloatImpl();
}

double Random::Double() 
{
    return Random::GetInstance().DoubleImpl();
}

uint16_t Random::InRange(uint16_t first, uint16_t last) 
{
    return Random::GetInstance().InRangeImpl(first, last);
}

float Random::FloatImpl() 
{
    std::uniform_real_distribution<> dist(0,1);
    return dist(eng_);
}

double Random::DoubleImpl() 
{
    std::uniform_real_distribution<> dist(0,1);
    return dist(eng_);
}


uint16_t Random::InRangeImpl(uint16_t first, uint16_t last) 
{
    std::cout << "Not HERE" << std::endl;
    std::uniform_int_distribution<uint16_t> dist(first, last);
    return dist(eng_);
}

uint32_t Random::InRangeImpl(uint32_t first, uint32_t last) 
{
    std::cout << "HERE" << std::endl;
    std::uniform_int_distribution<uint32_t> dist(first, last);
    return dist(eng_);
}