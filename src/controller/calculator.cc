#include "calculator.h"

#include <chrono>
#include <stdexcept>
#include <utility>

#include "graph.h"
#include "rpn.h"

double ns::CalculatorController::EvaluateExpression(std::string line) {
  return InfixToRpnConverter(line).Convert().Evaluate();
}

std::pair<std::vector<double>, std::vector<double>>
ns::CalculatorController::GetGraphPoints(std::string line, double startx,
                                          double stopx, double stepx) {
  if (line.find("x") == std::string::npos) {
    throw std::invalid_argument("No X found calculation pointless");
  }

  graph_.ParseExpression(line);

  auto begin = std::chrono::steady_clock::now();
  graph_.CalculateInRange(startx, stopx, startx, stopx, stepx);
  auto end = std::chrono::steady_clock::now();
  std::cout << "Calculation time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     begin)
                   .count()
            << " milliseconds" << std::endl;

  return std::make_pair(graph_.x(), graph_.y());
}
