#include <fstream>
#include <sstream>

#include "Util.h"

std::string Util::ReadFile(const std::string path)
{
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}