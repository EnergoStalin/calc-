#include "rpn.h"

#include <cmath>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <string>

ns::RpnExpression ns::InfixToRpnConverter::Convert() {
  Simplify();
  Validate();

  is_.str(line_);
  is_ >> std::skipws;

  char c;
  while (is_ >> c) {
    if (IsDoublePart(c)) {
      is_.unget();

      double number = 0;
      is_ >> number;

      os_ << number << " ";
    } else {
      if (CheckUnary(c)) {
        operators_.push(GetUnaryRepresentative(c));
      } else {
        HandleToken(c);
      }
    }
  }

  PopOperatorsUntilEmpty();

  return RpnExpression(os_.str().substr(0, os_.str().size() - 1));
}

void ns::InfixToRpnConverter::Simplify() {
  Replace("a(?:rc)?cos", Operations::ACOS);
  Replace("a(?:rc)?sin", Operations::ASIN);
  Replace("a(?:rc)?tan", Operations::ATAN);
  Replace("cos", Operations::COS);
  Replace("sin", Operations::SIN);
  Replace("tan", Operations::TAN);
  Replace("sqrt", Operations::SQRT);
  Replace("ln", Operations::LN);
  Replace("log", Operations::LOG);
  Replace("mod", Operations::MOD);

  line_ = std::regex_replace(line_, std::regex("\\s*"), "");
}

void ns::InfixToRpnConverter::Replace(std::string literal,
                                       Operations representative) {
  line_ = std::regex_replace(line_, std::regex(literal),
                             std::string(1, static_cast<char>(representative)));
}

int ns::InfixToRpnConverter::GetPriority(char c) {
  int res = -1;
  Operations op = static_cast<Operations>(c);

  if (op == Operations::PLUS || op == Operations::MINUS) {
    res = 1;
  } else if (op == Operations::MUL || op == Operations::DIV ||
             op == Operations::MOD) {
    res = 2;
  } else if (op == Operations::POW || op == Operations::UMINUS ||
             op == Operations::UPLUS) {
    res = 3;
  } else if (op == Operations::COS || op == Operations::SIN ||
             op == Operations::TAN || op == Operations::ACOS ||
             op == Operations::ASIN || op == Operations::ATAN ||
             op == Operations::SQRT || op == Operations::LN ||
             op == Operations::LOG) {
    res = 4;
  }

  return res;
}

bool ns::InfixToRpnConverter::IsOperator(char op) {
  return GetPriority(op) != -1;
}

void ns::InfixToRpnConverter::Validate() const {
  if (std::count(line_.begin(), line_.end(), '(') !=
      std::count(line_.begin(), line_.end(), ')')) {
    throw std::invalid_argument("Mismatched brackets");
  }
}

void ns::InfixToRpnConverter::PopOperatorsUntilEmpty() {
  while (!operators_.empty()) {
    os_ << operators_.top() << " ";
    operators_.pop();
  }
}

void ns::InfixToRpnConverter::UnloadStackPriorityWise(char op) {
  while (!operators_.empty() &&
         GetPriority(operators_.top()) >= GetPriority(op)) {
    os_ << operators_.top() << " ";
    operators_.pop();
  }

  operators_.push(op);
}

void ns::InfixToRpnConverter::HandleToken(char op) {
  if (op == ')') {
    HandleCloseBracket();
  } else if (op == '(') {
    operators_.push(op);
  } else if (op == 'x') {
    os_ << "x ";
  } else {
    UnloadStackPriorityWise(op);
  }
}

void ns::InfixToRpnConverter::HandleCloseBracket() {
  // When encountering closing bracket we need to pop operators until we
  // hit open bracket
  while (!operators_.empty() && operators_.top() != '(') {
    os_ << operators_.top() << " ";
    operators_.pop();
  }
  // Pop open bracket not shure why when not empty but it mostly works
  if (!operators_.empty()) {
    operators_.pop();
  }
}

// Some shady business with seekbehind since we stateless regardless previous
// token
bool ns::InfixToRpnConverter::CheckUnary(char op) {
  bool res = false;

  if (CanBeUnary(op)) {
    if (is_.tellg() <= 1) {
      res = true;
    } else {
      is_.seekg(-2, std::ios_base::cur);

      if (IsOperator(is_.peek()) || is_.peek() == '(') {
        res = true;
      }

      is_.seekg(2, std::ios_base::cur);
    }
  }

  return res;
}

bool ns::InfixToRpnConverter::CanBeUnary(char op) {
  return op == static_cast<char>(Operations::MINUS) ||
         op == static_cast<char>(Operations::PLUS);
}

bool ns::InfixToRpnConverter::IsDoublePart(char c) {
  return std::isdigit(c) || c == '.';
}

char ns::InfixToRpnConverter::GetUnaryRepresentative(char op) {
  char res = 0;

  if (op == static_cast<char>(Operations::MINUS)) {
    res = static_cast<char>(Operations::UMINUS);
  } else if (op == static_cast<char>(Operations::PLUS)) {
    res = static_cast<char>(Operations::UPLUS);
  }

  return res;
}

double ns::RpnExpression::Evaluate(double x) const {
  std::stack<double> numbers;
  std::istringstream is(rpn_);

  char c;
  while (is >> c) {
    if (InfixToRpnConverter::IsDoublePart(c)) {
      is.unget();
      double number = 0;
      is >> number;
      numbers.push(number);
    } else if (c == 'x') {
      numbers.push(x);
    } else {
      EvaluateOperation(numbers, c);
    }
  }

  return numbers.top();
}

void ns::RpnExpression::EvaluateOperation(std::stack<double> &numbers,
                                           char c) {
  if (IsBinaryOperator(c)) {
    if (numbers.empty()) {
      throw std::invalid_argument("Binary operator " + std::string(1, c) +
                                  " doesent have first operand");
    }

    double v1 = numbers.top();
    numbers.pop();

    if (numbers.empty()) {
      throw std::invalid_argument("Binary operator " + std::string(1, c) +
                                  " doesent have second operand");
    }

    double v2 = numbers.top();
    numbers.pop();

    numbers.push(ApplyBinaryOperator(c, v1, v2));
  } else {
    if (numbers.empty()) {
      throw std::invalid_argument("Unary operator " + std::string(1, c) +
                                  " doesent have operand");
    }

    double v1 = numbers.top();
    numbers.pop();

    numbers.push(ApplyUnaryOperator(c, v1));
  }
}

ns::RpnExpression::RpnExpression(std::string rpn) : rpn_(rpn) {}

bool ns::RpnExpression::IsBinaryOperator(char c) {
  return c == static_cast<char>(Operations::PLUS) ||
         c == static_cast<char>(Operations::MINUS) ||
         c == static_cast<char>(Operations::DIV) ||
         c == static_cast<char>(Operations::MUL) ||
         c == static_cast<char>(Operations::POW) ||
         c == static_cast<char>(Operations::MOD);
}

double ns::RpnExpression::ApplyUnaryOperator(char c, double v) {
  double res = 0;
  Operations op = static_cast<Operations>(c);

  if (op == Operations::UMINUS) {
    res = -v;
  } else if (op == Operations::UPLUS) {
    res = v;
  } else if (op == Operations::COS) {
    res = std::cos(v);
  } else if (op == Operations::SIN) {
    res = std::sin(v);
  } else if (op == Operations::TAN) {
    res = std::tan(v);
  } else if (op == Operations::ACOS) {
    res = std::acos(v);
  } else if (op == Operations::ASIN) {
    res = std::asin(v);
  } else if (op == Operations::ATAN) {
    res = std::atan(v);
  } else if (op == Operations::SQRT) {
    res = std::sqrt(v);
  } else if (op == Operations::LN) {
    res = std::log(v);
  } else if (op == Operations::LOG) {
    res = std::log10(v);
  } else {
    throw std::invalid_argument("Unknown unary operator " + std::string(1, c));
  }

  return res;
}

double ns::RpnExpression::ApplyBinaryOperator(char c, double v2, double v1) {
  double res = 0;
  Operations op = static_cast<Operations>(c);

  if (op == Operations::PLUS) {
    res = v1 + v2;
  } else if (op == Operations::MINUS) {
    res = v1 - v2;
  } else if (op == Operations::DIV) {
    if (v2 == 0) {
      throw std::invalid_argument("Division by zero");
    }
    res = v1 / v2;
  } else if (op == Operations::MUL) {
    res = v1 * v2;
  } else if (op == Operations::POW) {
    res = std::pow(v1, v2);
  } else if (op == Operations::MOD) {
    res = std::fmod(v1, v2);
  } else {
    throw std::invalid_argument("Unknown binary operator " + std::string(1, c));
  }

  return res;
}
