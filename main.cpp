#include <iostream>
#include <string>

#include "Runner.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Invalid arguments" << std::endl;
        return 1;
    }

    std::string file = argv[1];

    auto runner = Runner(file);
    runner.Run();

    if (runner.HadError())
    {
        return 1;
    }

    return 0;
}