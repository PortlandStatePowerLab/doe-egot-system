#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <ecs/sim_module.hpp>

class ECSTesting : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        /* Import module containing Position, Velocity and Move */
        ecs.import<simple_module>();
    }

    void TearDown() override
    {
    }

protected:
    flecs::world ecs;
};

TEST_F(ECSTesting, DeviceCapability) 
{   
    std::cout << "Hello" << std::endl;    
}