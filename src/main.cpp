#include <iostream>

#include "Lox.h"

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    std::string path(argv[2]);
    Lox::RunFile(path);
  }
  else
  {
    Lox::RunPrompt();
  }

  return 0;
}