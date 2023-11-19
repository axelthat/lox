#pragma once

#include <string>
#include <sstream>
#include <vector>

class Util
{
public:
  static std::vector<std::string> Split(const std::string &s, char delimiter);

  static inline std::string LTrim(std::string &s)
  {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
    return s;
  }

  static inline std::string RTrim(std::string &s)
  {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
    return s;
  }

  static inline std::string Trim(std::string &s)
  {
    RTrim(s);
    LTrim(s);
    return s;
  }
};