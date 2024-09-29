#pragma once

#include <string>
#include <optional>

#include "TokenType.h"

class Token
{
public:
    Token(const TokenType tokenType, const std::string lexeme, const std::optional<std::string> literal, const unsigned int line);

    std::string toString();

private:
    const TokenType m_TokenType;
    const std::string m_Lexeme;
    const std::optional<std::string> m_Literal;
    const unsigned int m_Line;
};