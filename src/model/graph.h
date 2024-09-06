// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_MODEL_GRAPH_H_
#define SRC_SRC_MODEL_GRAPH_H_

#include <vector>

#include "rpn.h"

namespace ns {

class Graph {
 public:
  Graph(std::string line);
  Graph();

  void ParseExpression(std::string line = "");
  void CalculateInRange(double x1, double x2, double y1, double y2,
                        double s = 0.01);
  void Clear();

  std::vector<double> x() const;
  std::vector<double> y() const;

 private:
  RpnExpression expr_;
  std::string infix_;

  std::vector<double> x_;
  std::vector<double> y_;

  std::pair<double, double> range_x_;
  std::pair<double, double> range_y_;
  double step_;
};

}  // namespace ns

#endif  //  SRC_SRC_MODEL_GRAPH_H_
