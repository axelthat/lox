#pragma once

#include <string>
#include <optional>

#include "TokenType.h"

class Token
{
private:
  const TokenType type;
  const std::string lexeme;
  const std::optional<std::string> literal;
  const int line;

public:
  Token(const TokenType &type, const std::string &lexeme, const std::optional<std::string> &literal, const int &line);

  inline const std::string toString() const
  {
    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " + literal.value_or("");
  }
};