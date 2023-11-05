#pragma once

#include <string>

class Lox
{
private:
  static bool HadError;

public:
  static void RunPrompt();
  static void RunFile(const std::string &path);

  static void Run(const std::string &source);

  static void Error(int line, const std::string &message);
  static void Report(int line, const std::string &where, const std::string &message);
};