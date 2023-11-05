#include "Token.h"

Token::Token(const TokenType &type, const std::string &lexeme, const std::optional<std::string> &literal, const int &line) : type(type),
                                                                                                                             lexeme(lexeme),
                                                                                                                             literal(literal),
                                                                                                                             line(line)
{
}