#include <string>
#include <gtest/gtest.h>
#include <https/https_client.hpp>

extern std::string g_program_path;

class HttpsClientTests : public ::testing::Test
{
protected:
    void SetUp() override 
    {        
    }

    void TearDown() override
    {
    }

protected:

};


TEST_F(HttpsClientTests, IsSampleValid)
{
    HttpsClient *client = HttpsClient::getInstance(g_program_path, "www.google.com", "443");
    try
    {
        auto resp = client->Get("/webhp");
        std::cout << resp << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    EXPECT_TRUE(false);
}
