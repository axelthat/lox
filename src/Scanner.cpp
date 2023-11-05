#include "Scanner.h"
#include "Lox.h"

Scanner::Scanner(const std::string &source) : source(source), tokens(), start(0), current(0), line(1)
{
}

const std::vector<Token> &Scanner::ScanTokens()
{
  while (!IsAtEnd())
  {
    start = current;
    ScanToken();
  }

  tokens.emplace_back(TokenType::END_OF_FILE, "", std::nullopt, line);
  return tokens;
}

void Scanner::ScanToken()
{
  const auto c = Advance();
  switch (c)
  {
  case '(':
    AddToken(TokenType::LEFT_PAREN);
    break;
  case ')':
    AddToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    AddToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    AddToken(TokenType::RIGHT_BRACE);
    break;
  case ',':
    AddToken(TokenType::COMMA);
    break;
  case '.':
    AddToken(TokenType::DOT);
    break;
  case '-':
    AddToken(TokenType::MINUS);
    break;
  case '+':
    AddToken(TokenType::PLUS);
    break;
  case ';':
    AddToken(TokenType::SEMICOLON);
    break;
  case '*':
    AddToken(TokenType::STAR);
    break;
  case '/':
    if (Match('/'))
    {
      while (Peek() != '\n' && !IsAtEnd())
        Advance();
    }
    else
    {
      AddToken(TokenType::SLASH);
    }
    break;
  case '!':
    AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;
  case '"':
    String();
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  default:
    if (IsDigit(c))
    {
      Number();
    }
    else
    {
      Lox::Error(line, "Unexpected character.");
    }
    break;
  }
}

void Scanner::AddToken(TokenType type, std::optional<std::string> literal = std::nullopt)
{
  auto text = source.substr(start, current);
  tokens.emplace_back(type, text, literal, line);
}

bool Scanner::Match(char expected)
{
  if (IsAtEnd())
    return false;

  if (source.at(current) != expected)
    return false;

  current++;
  return true;
}

void Scanner::String()
{
  while (Peek() != '"' && !IsAtEnd())
  {
    if (Peek() == '\n')
      line++;

    Advance();
  }

  if (IsAtEnd())
  {
    Lox::Error(line, "Unterminated string.");
    return;
  }

  Advance();

  const auto &string = source.substr(start + 1, current - 1);
  AddToken(TokenType::STRING, string);
}

void Scanner::Number()
{
  while (IsDigit(Peek()))
  {
    Advance();
  }

  if (Peek() == '.' && IsDigit(PeekNext()))
  {
    Advance();

    while (IsDigit(Peek()))
    {
      Advance();
    }
  }

  AddToken(TokenType::NUMBER, source.substr(start, current));
}