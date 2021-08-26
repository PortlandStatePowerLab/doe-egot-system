#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>         // std::chrono::seconds
#include <vector>
#include <gtest/gtest.h>
#include <https/combined_client.hpp>
#include <https/combined_client.hpp>
#include <https/https_server.hpp>

extern std::string g_program_path;



class DTMTesting : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        // do nothing
    }

    void TearDown() override
    {
        // do nothing
    }
};

TEST_F(DTMTesting, DeviceCapability) 
{   
    EXPECT_TRUE(true);
}
