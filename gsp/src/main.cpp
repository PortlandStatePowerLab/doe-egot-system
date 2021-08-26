#include <https/https_server.hpp>

std::string g_program_path;

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
};

int main(int argc, char** argv)
{
    GetParentPath(argv);
    std::string address = "0.0.0.0";
    uint16_t port = 443;
    HttpsServer gsp(address, port, g_program_path);
    try
    {
        gsp.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}