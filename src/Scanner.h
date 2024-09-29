#pragma once

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "Token.h"

class Runner;

class Scanner
{
public:
    Scanner(const std::string source);

    void ScanTokens();

private:
    const std::string m_Source;
    std::vector<Token> m_Tokens;
    std::unordered_map<std::string, TokenType> m_Keywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE},
    };
    unsigned int m_Start = 0;
    unsigned int m_Current = 0;
    unsigned int m_Line = 1;

    inline bool IsAtEnd() const;
    inline char Peek() const;
    inline char PeekNext() const;
    inline bool IsDigit(char c) const;
    inline bool IsAlpha(char c) const;
    inline bool IsAlphaNumeric(char c) const;
    char Advance();
    bool Match(const char expected);

    void ScanToken();
    void AddToken(const TokenType tokenType, const std::optional<std::string> literal = std::nullopt);

    void String();
    void Number();
    void Identifier();
};