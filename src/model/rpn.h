// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_MODEL_RPN_H_
#define SRC_SRC_MODEL_RPN_H_

#include <iostream>
#include <istream>
#include <sstream>
#include <stack>
#include <string>

namespace ns {

enum class Operations : char {
  // Binary operators
  MINUS = '-',
  PLUS = '+',
  DIV = '/',
  MUL = '*',
  POW = '^',

  // Unary tokens
  UMINUS = 'u',
  UPLUS = 'U',

  // Multibyte tokens
  COS = 'c',
  SIN = 's',
  TAN = 't',
  ACOS = 'C',
  ASIN = 'S',
  ATAN = 'T',
  SQRT = 'q',
  LN = 'n',
  LOG = 'l',
  MOD = '%',
};

class RpnExpression {
 public:
  RpnExpression(std::string rpn);

  double Evaluate(double x = 0) const;
  std::string GetRpn() const { return rpn_; }

 private:
  std::string rpn_;

  static bool IsBinaryOperator(char);
  static double ApplyBinaryOperator(char, double, double);
  static double ApplyUnaryOperator(char, double);
  static void EvaluateOperation(std::stack<double>&, char);
};

class InfixToRpnConverter {
 public:
  InfixToRpnConverter(std::string line)
      : original_(line), line_(line), operators_(), os_() {}
  RpnExpression Convert();

  static bool IsDoublePart(char c);
  static bool IsOperator(char op);

 private:
  std::string original_;
  std::string line_;

  std::stack<char> operators_;

  std::ostringstream os_;
  std::istringstream is_;

  /**
   * Replace all functions in the line to avoid parsing multibyte tokens
   */
  void Simplify();
  void Replace(std::string literal, Operations representative);

  void HandleToken(char op);
  void PopOperatorsUntilEmpty();
  void UnloadStackPriorityWise(char op);
  void HandleCloseBracket();

  bool CheckUnary(char op);

  void Validate() const;

  static int GetPriority(char op);
  static bool CanBeUnary(char op);
  static char GetUnaryRepresentative(char op);
};

};  // namespace ns

#endif  //  SRC_SRC_MODEL_RPN_H_
