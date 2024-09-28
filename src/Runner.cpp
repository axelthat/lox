#include <iostream>

#include "Runner.h"
#include "Util.h"
#include "Scanner.h"

bool Runner::m_HadError = false;

Runner::Runner(std::string path) : m_Source(Util::ReadFile(path))
{
}

void Runner::Run() const
{
    Scanner scanner(m_Source);
    scanner.ScanTokens();
}

bool Runner::HadError()
{
    return m_HadError;
}

void Runner::Error(unsigned int line, std::string message)
{
    Report(line, "", message);
}

void Runner::Report(unsigned int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message;
    m_HadError = true;
}