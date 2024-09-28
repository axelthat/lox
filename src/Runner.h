#pragma once

#include <string>

class Runner
{
public:
    Runner(const std::string path);

    void Run() const;
    static bool HadError();

private:
    const std::string m_Source;
    static bool m_HadError;

    static void Error(unsigned int line, std::string message);
    static void Report(unsigned int line, std::string where, std::string message);
};