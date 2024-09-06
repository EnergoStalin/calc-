#include "calc.h"

#include <string>

#include "rpn.h"

double ns::Calculator::Calculate(std::string line) {
  return InfixToRpnConverter(line).Convert().Evaluate();
}
