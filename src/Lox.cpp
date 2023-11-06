#include <iostream>
#include <fstream>
#include <sstream>

#include "Lox.h"
#include "Scanner.h"

bool Lox::HadError = false;

void Lox::RunFile(const std::string &path)
{
  std::ifstream file(path);

  std::stringstream stream;
  stream << file.rdbuf();

  auto contents = stream.str();

  file.close();

  Lox::Run(contents);
}

void Lox::RunPrompt()
{
  std::string input;
  std::getline(std::cin, input);

  Lox::Run(input);
}

void Lox::Run(const std::string &source)
{
  auto scanner = Scanner(source);
  auto tokens = scanner.ScanTokens();

  for (const auto &token : tokens)
  {
    // std::cout << token << std::endl;
  }
}

void Lox::Error(int line, const std::string &message)
{
  Report(line, "", message);
}

void Lox::Report(int line, const std::string &where, const std::string &message)
{
  std::cout << "[line \"" << line << "\"] Error" << where << ": " << message << std::endl;
  HadError = true;
}