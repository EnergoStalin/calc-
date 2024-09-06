#include "graph.h"

void ns::Graph::CalculateInRange(double x1, double x2, double y1, double y2,
                                  double s) {
  std::pair<double, double> range_x = {x1, x2};
  std::pair<double, double> range_y = {y1, y2};

  // Do not recalculate for same range twice
  if (range_x_ == range_x && range_y_ == range_y && step_ == s) {
    return;
  }

  range_x_ = range_x;
  range_y_ = range_y;
  step_ = s;

  for (double x = x1; x <= x2; x += s) {
    x_.push_back(x);
    y_.push_back(expr_.Evaluate(x));
  }
}
std::vector<double> ns::Graph::y() const { return y_; }

std::vector<double> ns::Graph::x() const { return x_; }

void ns::Graph::ParseExpression(std::string infix) {
  // Do not recalculate for same expression
  if (!infix.empty() && infix_ == infix) {
    return;
  }

  // Allow passing empty line to use interanlly saved in constructor
  if (!infix.empty()) {
    infix_ = infix;
  }

  if (infix_.empty()) {
    throw std::invalid_argument("Empty expression");
  }

  Clear();
  expr_ = InfixToRpnConverter(infix_).Convert();
}

void ns::Graph::Clear() {
  x_.clear();
  y_.clear();
  range_x_.first = 0;
  range_x_.second = 0;
  range_y_.first = 0;
  range_y_.second = 0;
  step_ = 0.01;
}

ns::Graph::Graph() : Graph("") {}

ns::Graph::Graph(std::string line)
    : expr_(""),
      infix_(line),
      x_(),
      y_(),
      range_x_(),
      range_y_(),
      step_(0.01) {}
