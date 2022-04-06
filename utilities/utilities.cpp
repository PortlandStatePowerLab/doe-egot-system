#include "include/utilities/utilities.hpp"
#include <fstream>
#include <sstream>
#include <chrono>

namespace psu
{
    namespace utilities
    {
        std::string readFile(const std::string &filename)
        {
            std::string content;

            std::ifstream ifs(filename);
            if (ifs)
            {
                std::ostringstream oss;
                oss << ifs.rdbuf();

                content = oss.str();
            }
            else
            {
                content = "";
            };
            ifs.close();
            return content;
        }

        std::string getProgramPath(char **arg)
        {
            std::string path = arg[0];
            size_t found = path.find_last_of("/\\");
            return path.substr(0, found);
        }

        uint64_t getTime()
        {
            auto time = std::chrono::system_clock::now();
            return time.time_since_epoch().count();
        }
    } // namespace utilities

} // namespace psu