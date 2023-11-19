#pragma once

#include "Expr.h"
#include "Token.h"

class Binary : public Expr
{
private:
  const Expr left;
  const Token opr;
  const Expr right;

public:
  Binary(const Expr &left, const Token &opr, const Expr &right);
};