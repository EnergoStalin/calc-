// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_CONTROLLER_CALCULATOR_H_
#define SRC_SRC_CONTROLLER_CALCULATOR_H_

#include <model.h>

#include <string>
#include <vector>

#include "graph.h"

namespace ns {
class CalculatorController {
 public:
  /**
   * @brief The EvaluateExpression function evaluates an expression and returns
   * the result.
   *
   * @param line The expression to evaluate.
   * @return The result of the expression.
   * @throws std::runtime_error If the expression is invalid.
   */
  double EvaluateExpression(std::string line);

  /**
   * @brief The GetGraphPoints function returns a vector of points on a graph
   * based on the input line, startx, stopx, and stepx.
   *
   * @param line The expression to evaluate.
   * @param startx The starting x-coordinate of the graph.
   * @param stopx The ending x-coordinate of the graph.
   * @param stepx The step size of the x-coordinate of the graph.
   * @return A vector of points on the graph.
   * @throws std::runtime_error If the expression is invalid.
   */
  std::pair<std::vector<double>, std::vector<double>> GetGraphPoints(
      std::string line, double startx, double stopx, double stepx);

 private:
  Graph graph_;
};
}  // namespace ns

#endif  //  SRC_SRC_CONTROLLER_CALCULATOR_H_
