#include "Util.h"

std::vector<std::string> Util::Split(const std::string &s, char delimiter)
{
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delimiter))
  {
    result.push_back(item);
  }

  return result;
}