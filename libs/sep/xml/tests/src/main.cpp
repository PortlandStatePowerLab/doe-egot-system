#include <gtest/gtest.h>
#include <utilities/utilities.hpp>

std::string g_program_path;

int main(int argc, char **argv) 
{
    g_program_path = psu::utilities::getProgramPath(argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
