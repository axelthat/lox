// AUTOMATICALLY GENERATED
// -- Scripts/GenerateAst.cpp

#pragma once

#include "Type.h"
#include "Token.h"

namespace Expr {
  class Expr {};

  class Binary: public Expr {
    private:
      Expr left;
      Token opr;
      Expr right;

    public:
      Binary(
        Expr left,
        Token opr,
        Expr right
      ):
        left(left),
        opr(opr),
        right(right)
      {}
  };

  class Grouping: public Expr {
    private:
      Expr expression;

    public:
      Grouping(
        Expr expression
      ):
        expression(expression)
      {}
  };

  class Literal: public Expr {
    private:
      Object value;

    public:
      Literal(
        Object value
      ):
        value(value)
      {}
  };

  class Unary: public Expr {
    private:
      Token opr;
      Expr right;

    public:
      Unary(
        Token opr,
        Expr right
      ):
        opr(opr),
        right(right)
      {}
  };

};