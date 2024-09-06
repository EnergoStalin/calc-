#include "graph.h"

#include <gtest/gtest.h>
#include <model.h>

TEST(Graph, EpmtyExpression) {
  ns::Graph graph;

  EXPECT_THROW(graph.ParseExpression(), std::invalid_argument);
}

TEST(Graph, GetGraphPoints) {
  ns::Graph graph;

  graph.ParseExpression("x^2");
  graph.ParseExpression("x^2");

  graph.CalculateInRange(0, 10, 0, 10);
  EXPECT_EQ(graph.x().size(), 1001);
  EXPECT_EQ(graph.y().size(), 1001);
  graph.CalculateInRange(0, 10, 0, 10);
  EXPECT_EQ(graph.x().size(), 1001);
  EXPECT_EQ(graph.y().size(), 1001);
}
