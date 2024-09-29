#include <optional>
#include <iostream>

#include "Scanner.h"
#include "Runner.h"

Scanner::Scanner(const std::string source) : m_Source(source)
{
}

void Scanner::ScanTokens()
{
    while (!IsAtEnd())
    {
        m_Start = m_Current;
        ScanToken();
    }

    m_Tokens.emplace_back(TokenType::END_OF_FILE, "", std::nullopt, m_Line);

    for (auto token : m_Tokens)
    {
        std::cout << token.toString() << std::endl;
    }
}

bool Scanner::IsAtEnd() const
{
    return m_Current >= m_Source.length();
}

char Scanner::Peek() const
{
    if (IsAtEnd())
        return '\0';

    return m_Source.at(m_Current);
}

char Scanner::PeekNext() const
{
    if (m_Current + 1 >= m_Source.length())
        return '\0';
    return m_Source.at(m_Current + 1);
}

bool Scanner::IsDigit(char c) const
{
    return c >= '0' && c <= '9';
}

bool Scanner::IsAlpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::IsAlphaNumeric(char c) const
{
    return IsAlpha(c) || IsDigit(c);
}

bool Scanner::Match(const char expected)
{
    if (IsAtEnd())
        return false;

    if (m_Source.at(m_Current) != expected)
        return false;

    m_Current++;
    return true;
}

char Scanner::Advance()
{
    return m_Source.at(m_Current++);
}

void Scanner::ScanToken()
{
    char c = Advance();

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
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    case '\n':
        m_Line++;
        break;
    default:
        if (IsDigit(c))
        {
            Number();
        }
        else if (IsAlpha(c))
        {
            Identifier();
        }
        else
        {
            Runner::Error(m_Line, "Unexpected character.");
        }
        break;
    }
}

void Scanner::AddToken(const TokenType tokenType, const std::optional<std::string> literal)
{
    auto text = m_Source.substr(m_Start, m_Current);
    m_Tokens.emplace_back(tokenType, text, literal, m_Line);
}

void Scanner::String()
{
    while (Peek() != '"' && !IsAtEnd())
    {
        if (Peek() == '\n')
            m_Line++;
        Advance();
    }

    if (IsAtEnd())
    {
        Runner::Error(m_Line, "Unterminated string");
        return;
    }

    Advance();

    auto value = m_Source.substr(m_Start + 1, m_Current - 1);
    AddToken(TokenType::STRING, value);
}

void Scanner::Number()
{
    while (IsDigit(Peek()))
        Advance();

    if (Peek() == '.' && IsDigit(PeekNext()))
    {
        Advance();

        while (IsDigit(Peek()))
            Advance();
    }

    AddToken(TokenType::NUMBER, m_Source.substr(m_Start, m_Current));
}

void Scanner::Identifier()
{
    while (IsAlphaNumeric(Peek()))
        Advance();

    auto text = m_Source.substr(m_Start, m_Current);
    auto type = TokenType::IDENTIFIER;

    if (m_Keywords.contains(text))
    {
        type = m_Keywords[text];
    }

    AddToken(type);
}