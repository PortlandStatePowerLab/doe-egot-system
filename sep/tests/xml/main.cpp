#include <gtest/gtest.h>
#include "global.hpp"

std::string g_program_path;

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
};

int main(int argc, char **argv) 
{
    GetParentPath(argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
