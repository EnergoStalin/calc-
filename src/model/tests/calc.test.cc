#include <gtest/gtest.h>

#include <cmath>

#include "rpn.h"

#define EPS 1e-7

TEST(InfixToRpnConverter, Convert) {
  EXPECT_EQ(ns::InfixToRpnConverter("1+1").Convert().GetRpn(), "1 1 +");
}

TEST(InfixToRpnConverter, MismatchedBrackets) {
  EXPECT_THROW(ns::InfixToRpnConverter("1/0)").Convert().GetRpn(),
               std::invalid_argument);
}

TEST(InfixToRpnConverter, ConvertOnLargeEquations) {
  EXPECT_EQ(ns::InfixToRpnConverter("2*(3+4)-5/2").Convert().GetRpn(),
            "2 3 4 + * 5 2 / -");
  EXPECT_EQ(
      ns::InfixToRpnConverter("2 * ( 3 + 4 ) - 5 / 2").Convert().GetRpn(),
      "2 3 4 + * 5 2 / -");
  EXPECT_EQ(
      ns::InfixToRpnConverter("(2 + 3) * (4 - 5) / 6").Convert().GetRpn(),
      "2 3 + 4 5 - * 6 /");
  EXPECT_EQ(
      ns::InfixToRpnConverter("2 * (3 + -4) - (5 / 2)").Convert().GetRpn(),
      "2 3 4 u + * 5 2 / -");
  EXPECT_EQ(ns::InfixToRpnConverter("2 * (3 + 4) - (5 / (2 + 3))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / -");
  EXPECT_EQ(ns::InfixToRpnConverter("2 * (3 ^ 4) - (5 / (2 + 3))")
                .Convert()
                .GetRpn(),
            "2 3 4 ^ * 5 2 3 + / -");
}

TEST(InfixToRpnConverter, ConvertX) {
  EXPECT_EQ(ns::InfixToRpnConverter(
                "-cos(2) * sin(3) + tan(x) / arccos(3) - arcsin(2) + "
                "arctan(3)")
                .Convert()
                .GetRpn(),
            "2 c u 3 s * x t 3 C / + 2 S - 3 T +");
  EXPECT_EQ(ns::InfixToRpnConverter("-x").Convert().GetRpn(), "x u");
  EXPECT_EQ(ns::InfixToRpnConverter("-x + x").Convert().GetRpn(), "x u x +");
  EXPECT_EQ(ns::InfixToRpnConverter("x + x").Convert().GetRpn(), "x x +");
}

TEST(InfixToRpnConverter, ConvertLargeEquationsWithFunctions) {
  EXPECT_EQ(
      ns::InfixToRpnConverter("sin((2 + 3) * (4 - 5) / 6)").Convert().GetRpn(),
      "2 3 + 4 5 - * 6 / s");
  EXPECT_EQ(
      ns::InfixToRpnConverter("tan(2 * (3 + 4) - (5 / 2))").Convert().GetRpn(),
      "2 3 4 + * 5 2 / - t");
  EXPECT_EQ(ns::InfixToRpnConverter("arccos(2 * (3 + 4) - (5 / (2 + 3)))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / - C");
  EXPECT_EQ(ns::InfixToRpnConverter("arcsin(2 * (3 + 4) - (5 / (2 + 3)))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / - S");
  EXPECT_EQ(ns::InfixToRpnConverter("arctan(2 * (3 + 4) - (5 / (2 + 3)))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / - T");
  EXPECT_EQ(ns::InfixToRpnConverter("sqrt(2 * (3 + 4) - (5 / (2 + 3)))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / - q");
  EXPECT_EQ(ns::InfixToRpnConverter("log(2 * (3 + 4) - (5 / (2 + 3)))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / - l");
  EXPECT_EQ(ns::InfixToRpnConverter("ln(2 * (3 + 4) - (5 / (2 + 3)))")
                .Convert()
                .GetRpn(),
            "2 3 4 + * 5 2 3 + / - n");
}

TEST(InfixToRpnConverter, ExponentialConvert) {
  EXPECT_EQ(ns::InfixToRpnConverter("1e-5").Convert().GetRpn(), "1e-05");
  EXPECT_EQ(ns::InfixToRpnConverter("1e+5").Convert().GetRpn(), "100000");
  EXPECT_EQ(ns::InfixToRpnConverter("727e+50").Convert().GetRpn(), "7.27e+52");
  EXPECT_EQ(ns::InfixToRpnConverter("1E-5").Convert().GetRpn(), "1e-05");
}

TEST(InfixToRpnConverter, Unary) {
  EXPECT_EQ(
      ns::InfixToRpnConverter("-cos(-------2) * sin(3)").Convert().GetRpn(),
      "2 u u u u u u u c u 3 s *");
  EXPECT_EQ(
      ns::InfixToRpnConverter("-cos(-2------2) * sin(3)").Convert().GetRpn(),
      "2 u 2 u u u u u - c u 3 s *");
  EXPECT_EQ(
      ns::InfixToRpnConverter("-cos(2------2) * sin(3)").Convert().GetRpn(),
      "2 2 u u u u u - c u 3 s *");
  EXPECT_EQ(ns::InfixToRpnConverter("-2 * ++3").Convert().GetRpn(),
            "2 u 3 U U *");
  EXPECT_EQ(ns::InfixToRpnConverter("-2 * -(+3)").Convert().GetRpn(),
            "2 u 3 U u *");
}

TEST(InfixToRpnConverter, ConvertFunctions) {
  EXPECT_EQ(ns::InfixToRpnConverter("tan(2) / arccos(3)").Convert().GetRpn(),
            "2 t 3 C /");
  EXPECT_EQ(
      ns::InfixToRpnConverter("arcsin(2) + arctan(3)").Convert().GetRpn(),
      "2 S 3 T +");
  EXPECT_EQ(ns::InfixToRpnConverter("2mod3").Convert().GetRpn(), "2 3 %");
}

TEST(InfixToRpnConverter, ConvertFunctionsAndOperations) {
  EXPECT_EQ(ns::InfixToRpnConverter(
                "-cos(2) * sin(3) + tan(2) / arccos(3) - arcsin(2) + arctan(3)")
                .Convert()
                .GetRpn(),
            "2 c u 3 s * 2 t 3 C / + 2 S - 3 T +");
}

TEST(InfixToRpnConverter, ExponentialCalc) {
  ASSERT_NEAR(ns::InfixToRpnConverter("-1e-5 + 1e-5").Convert().Evaluate(),
              -1e-5 + 1e-5, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("-1e+5 + 1e-5").Convert().Evaluate(),
              -1e+5 + 1e-5, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("1e+5").Convert().Evaluate(), 1e+5, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("727e+50").Convert().Evaluate(), 727e+50,
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("1E-5").Convert().Evaluate(), 1e-5, EPS);
}

TEST(InfixToRpnConverter, ExponentialError) {
  EXPECT_THROW(
      ns::InfixToRpnConverter("-(1e)-5 + (1e-5)").Convert().Evaluate(),
      std::invalid_argument);
  EXPECT_THROW(
      ns::InfixToRpnConverter("-(1)e-5 + 1e(-(5))").Convert().Evaluate(),
      std::invalid_argument);
}

TEST(InfixToRpnConverter, Evaluate) {
  ASSERT_NEAR(ns::InfixToRpnConverter("1 + 1").Convert().Evaluate(), 2, EPS);
  ASSERT_NEAR(
      ns::InfixToRpnConverter("2 * ( 3 + 4 ) - 5 / 2").Convert().Evaluate(),
      11.5, EPS);
  ASSERT_NEAR(
      ns::InfixToRpnConverter("(2 + 3) * (4 - 5) / 6").Convert().Evaluate(),
      -0.83333333333333337, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("2 * (3 + 4) - (5 / (2 + 3))")
                  .Convert()
                  .Evaluate(),
              13, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("2 * (3 ^ 4) - (5 / (2 + 3))")
                  .Convert()
                  .Evaluate(),
              161, EPS);
}

TEST(InfixToRpnConverter, EvaluateFunctions) {
  ASSERT_NEAR(ns::InfixToRpnConverter("cos(2)").Convert().Evaluate(), cos(2),
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("sin(3)").Convert().Evaluate(), sin(3),
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("tan(4)").Convert().Evaluate(), tan(4),
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("arcsin(1)").Convert().Evaluate(),
              asin(1), EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("arctan(7)").Convert().Evaluate(),
              atan(7), EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("sqrt(8)").Convert().Evaluate(), sqrt(8),
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("log(9)").Convert().Evaluate(), log10(9),
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("ln(10)").Convert().Evaluate(), log(10),
              EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("3mod2").Convert().Evaluate(), 1, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("arccos(0.5)").Convert().Evaluate(),
              acos(0.5), EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("2 * (3 + 4) - (5 / (2 + 3))")
                  .Convert()
                  .Evaluate(),
              13, EPS);
  ASSERT_NEAR(ns::InfixToRpnConverter("2 * (3 ^ 4) - (5 / (2 + 3))")
                  .Convert()
                  .Evaluate(),
              161, EPS);
}

TEST(InfixToRpnConverter, EvaluateFunctionsLarge) {
  ASSERT_NEAR(ns::InfixToRpnConverter("-cos(2) * sin(3)").Convert().Evaluate(),
              -cos(2) * sin(3), EPS);
}

TEST(InfixToRpnConverter, Pow) {
  ASSERT_NEAR(ns::InfixToRpnConverter("2 ^ 3").Convert().Evaluate(),
              std::pow(2, 3), EPS);
}

TEST(InfixToRpnConverter, InvalidExpressions) {
  EXPECT_THROW(ns::InfixToRpnConverter("-cos2) * sin(3)").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("-cos() * sin(3)").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("  * sin(3)").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("-o() * sin(3)").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("5 / 0").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("arc(5)").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("orc(5)").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("o5").Convert().Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("ghsjdgsdh7357235gz&2%@)$+_)*l4753")
                   .Convert()
                   .Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("***#*#*###*##@#$@^&#()#@%!^$@")
                   .Convert()
                   .Evaluate(),
               std::invalid_argument);
  EXPECT_THROW(ns::InfixToRpnConverter("0-#*#*###*##@#$@^&#()#@%!^$@")
                   .Convert()
                   .Evaluate(),
               std::invalid_argument);
}

TEST(InfixToRpnConverter, EvaluateX) {
  EXPECT_NEAR(ns::InfixToRpnConverter("-x + x").Convert().Evaluate(4), 0, EPS);
  EXPECT_NEAR(ns::InfixToRpnConverter("x + x").Convert().Evaluate(4), 8, EPS);
  EXPECT_NEAR(ns::InfixToRpnConverter("sin(-x)").Convert().Evaluate(90),
              std::sin(-90), EPS);

  EXPECT_NEAR(ns::InfixToRpnConverter("2 + x * 3").Convert().Evaluate(90),
              2 + 90 * 3, EPS);

  auto expr = ns::InfixToRpnConverter("sin(-x)").Convert();
  EXPECT_NEAR(expr.Evaluate(90), std::sin(-90), EPS);
  EXPECT_NEAR(expr.Evaluate(15), std::sin(-15), EPS);
  EXPECT_NEAR(expr.Evaluate(32), std::sin(-32), EPS);
}
