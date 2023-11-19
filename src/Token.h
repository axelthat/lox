#pragma once

#include <string>
#include <optional>

#include "TokenType.h"
#include "Type.h"

class Token
{
private:
  const TokenType type;
  const std::string lexeme;
  const std::optional<Object> literal;
  const int line;

public:
  Token(const TokenType &type, const std::string &lexeme, const std::optional<Object> &literal, const int &line);

  inline const std::string toString() const
  {
    std::string literalValue = "";
    if (literal.has_value())
    {
      literalValue = std::get<std::string>(literal.value());
    }

    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " + literalValue;
  }
};