#include <string>
#include <gtest/gtest.h>
#include <https/https_server.hpp>

extern std::string g_program_path;

class HttpsServerTests : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        https_server = new HttpsServer("0.0.0.0", 8080, g_program_path);
        https_server->Run();
    }

    void TearDown() override
    {
        delete https_server;
    }

protected:
    HttpsServer* https_server;
};

TEST_F(HttpsServerTests, IsSampleValid) 
{   

    EXPECT_TRUE(false);      
}
