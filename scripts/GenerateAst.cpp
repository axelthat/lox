#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

#include "../src/Util.h"

static constexpr char SPACE[3] = "  ";

class GenerateAst
{
public:
  static void DefineAst(const std::string &outputDir, const std::string &baseName, const std::array<const std::string, 4> types);
  static void DefineType(std::ostringstream &ss, const std::string &baseName, const std::string &className, const std::string &fieldList);
};

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: generate_ast <output_directory>" << std::endl;
    return 1;
  }

  // clang-format off
  GenerateAst::DefineAst(argv[1], "Expr", {
    "Binary   : Expr left, Token opr, Expr right",
    "Grouping : Expr expression",
    "Literal  : Object value",
    "Unary    : Token opr, Expr right"
  });
  // clang-format on

  return 0;
}

void GenerateAst::DefineAst(const std::string &outputDir, const std::string &baseName, const std::array<const std::string, 4> types)
{
  const auto basePath = outputDir + "/" + baseName;
  const auto ccPath = basePath + ".cpp";
  const auto hPath = basePath + ".h";

  std::ostringstream ss;
  ss << "#pragma once" << std::endl;
  ss << std::endl;
  ss << "#include \"Type.h\"" << std::endl;
  ss << "#include \"Token.h\"" << std::endl;
  ss << std::endl;
  ss << "namespace Expr {" << std::endl;
  ss << SPACE << "class Expr {};" << std::endl;
  ss << std::endl;

  for (const auto &type : types)
  {
    auto vc = Util::Split(type, ':');
    std::string className = Util::Trim(vc[0]);
    std::string fieldList = Util::Trim(vc[1]);
    DefineType(ss, baseName, className, fieldList);
  }

  ss << "};" << std::endl;

  std::ofstream out(hPath);
  if (!out)
  {
    std::cerr << "Could not open file for writing." << std::endl;
    return;
  }

  out << ss.str();
  out.close();
}

void GenerateAst::DefineType(std::ostringstream &ss, const std::string &baseName, const std::string &className, const std::string &fieldList)
{
  ss << SPACE << "class " << className << ": public " << baseName << " {" << std::endl;
  ss << SPACE << "private:" << std::endl;

  auto fields = Util::Split(fieldList, ',');
  for (auto &field : fields)
  {
    Util::Trim(field);
  }

  for (auto &field : fields)
  {
    ss << SPACE << SPACE << field << ";" << std::endl;
  }

  ss << std::endl;
  ss << SPACE << "public:" << std::endl;
  ss << SPACE << SPACE << className << "(";

  for (size_t i = 0; i < fields.size(); ++i)
  {
    ss << fields[i];
    if (i < fields.size() - 1)
    {
      ss << ", ";
    }
  }

  ss << "): ";

  for (size_t i = 0; i < fields.size(); ++i)
  {
    auto name = Util::Split(fields[i], ' ')[1];
    ss << name << "(" << name << ")";
    if (i < fields.size() - 1)
    {
      ss << ", ";
    }
  }

  ss << " {};" << std::endl;
  ss << SPACE << "};" << std::endl;
  ss << std::endl;
}