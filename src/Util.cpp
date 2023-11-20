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

std::string Util::ReadFile(const std::string &path)
{
  std::ifstream file(path);
  if (!file.is_open())
  {
    throw std::runtime_error("File \"" + path + "\" not found!");
  }

  std::stringstream stream;
  stream << file.rdbuf();

  auto contents = stream.str();

  file.close();

  return contents;
}