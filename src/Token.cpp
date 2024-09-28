#include "Token.h"

Token::Token(const TokenType tokenType, const std::string lexeme, const std::string literal, const unsigned int line) : m_TokenType(tokenType), m_Lexeme(lexeme), m_Literal(literal), m_Line(line) {};

std::string Token::toString()
{
    return "";
}