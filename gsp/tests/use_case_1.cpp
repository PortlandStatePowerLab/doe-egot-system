#include <iostream>
#include <gtest/gtest.h>

class UseCase1 : public ::testing::Test 
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

protected:

};

TEST_F(UseCase1, HelloWorld) 
{   
    std::cout << "Hello World" << std::endl;    
}