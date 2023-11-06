#pragma once

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "Token.h"

class Lox;

class Scanner
{
private:
  const std::string &source;
  std::vector<Token> tokens;

  std::unordered_map<std::string, TokenType> keywords;
  unsigned int start;
  unsigned int current;
  unsigned int line;

public:
  Scanner(const std::string &source);

  const std::vector<Token> &ScanTokens();

private:
  inline bool IsDigit(char c) const
  {
    return c >= '0' && c <= '9';
  }

  inline bool IsAtEnd() const
  {
    return current >= source.length();
  };

  inline const char Advance()
  {
    return source.at(current++);
  }

  inline const char Peek() const
  {
    if (IsAtEnd())
      return '\0';

    return source.at(current);
  }

  inline const char PeekNext() const
  {
    if (current + 1 >= source.length())
      return '\0';

    return source.at(current + 1);
  }

  inline bool IsAlpha(char c) const
  {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
  }

  inline bool IsAlphaNumeric(char c)
  {
    return IsAlpha(c) || IsDigit(c);
  }

  void InitKeywords();

  bool Match(char expected);
  void String();
  void Number();
  void Identifier();

  void ScanToken();
  void AddToken(TokenType type, std::optional<std::string> literal = std::nullopt);
};