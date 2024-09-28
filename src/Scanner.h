#pragma once

#include <string>

class Scanner
{
public:
    Scanner(const std::string source);

    void ScanTokens() const;

private:
    const std::string m_Source;
};