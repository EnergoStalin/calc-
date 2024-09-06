#include "../deposit.h"

#include <gtest/gtest.h>

#define EPS 1e-7

TEST(Deposit, Stats1) {
  auto d = ns::Deposit(ns::Deposit::DepositConditions(1000, 12, 20));

  auto stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 1000, EPS);
  EXPECT_NEAR(stats.percents, 200, EPS);

  d = ns::Deposit(ns::Deposit::DepositConditions(1000, 12, 20, 10));

  stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 1000, EPS);
  EXPECT_NEAR(stats.percents, 200, EPS);

  d = ns::Deposit(
      ns::Deposit::DepositConditions(1000, 12, 20, 1000, 500, 10));

  stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 7000, EPS);
  EXPECT_NEAR(stats.percents, 200, EPS);

  d = ns::Deposit(ns::Deposit::DepositConditions(350000, 9, 4.7, 0, 0, 0));

  stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 350000, EPS);
  EXPECT_NEAR(stats.percents, 12337.5, EPS);
}

TEST(Deposit, Stats2) {
  using PayingPeriod = ns::Deposit::DepositConditions::PayingPeriod;

  auto d = ns::Deposit(
      ns::Deposit::DepositConditions(350000, 12, 4.7, PayingPeriod::YEAR, 0));

  auto stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 366450, EPS);
  EXPECT_NEAR(stats.percents, 16450, EPS);

  d = ns::Deposit(ns::Deposit::DepositConditions(
      350000, 9, 4.7, PayingPeriod::MONTH, 0, 0, 0));

  stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 362532.56435153, EPS);
  EXPECT_NEAR(stats.percents, 12532.56435153, EPS);

  d = ns::Deposit(ns::Deposit::DepositConditions(
      350000, 9, 4.7, PayingPeriod::QUARTAL, 0, 0, 15));

  stats = d.Stats();
  EXPECT_NEAR(stats.tax, 0, EPS);
  EXPECT_NEAR(stats.sum, 362483.03340703, EPS);
  EXPECT_NEAR(stats.percents, 12483.03340703, EPS);
}

TEST(DepositConditions, Validate) {
  EXPECT_FALSE(ns::Deposit::DepositConditions(-1, -2, -5).Validate());
  EXPECT_FALSE(ns::Deposit::DepositConditions(0, -2, -5).Validate());
  EXPECT_TRUE(ns::Deposit::DepositConditions(1, 2, 5).Validate());
}
