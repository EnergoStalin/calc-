#include "../credit.h"

#include <gtest/gtest.h>

#define EPS 1e-7

TEST(Credit, Stats) {
  auto d = ns::Credit(10000, 12 * 5, 13, ns::Credit::ANNUENT);

  auto stats = d.Stats();
  EXPECT_NEAR(stats.first_monthly_payment, 227.53073044, EPS);
  EXPECT_NEAR(stats.total_payment, 13651.84382653, EPS);
  EXPECT_NEAR(stats.overpayment_on_credit, 3651.843826537, EPS);

  d = ns::Credit(105000, 12 * 5, 20, ns::Credit::ANNUENT);

  stats = d.Stats();
  EXPECT_NEAR(stats.first_monthly_payment, 2781.85779007, EPS);
  EXPECT_NEAR(stats.total_payment, 166911.4674044, EPS);
  EXPECT_NEAR(stats.overpayment_on_credit, 61911.4674044, EPS);

  d = ns::Credit(10000, 12 * 5, 13, ns::Credit::DIFFERENTIAL);

  stats = d.Stats();
  EXPECT_NEAR(stats.first_monthly_payment, 274.9966666, EPS);
  EXPECT_NEAR(stats.last_monthly_payment, 168.47, EPS);
  EXPECT_NEAR(stats.total_payment, 13304.16, EPS);
  EXPECT_NEAR(stats.overpayment_on_credit, 3304.16, EPS);

  d = ns::Credit(105000, 12 * 2, 20, ns::Credit::DIFFERENTIAL);

  stats = d.Stats();
  EXPECT_NEAR(stats.first_monthly_payment, 6125, EPS);
  EXPECT_NEAR(stats.last_monthly_payment, 4447.92, EPS);
  EXPECT_NEAR(stats.total_payment, 126875, EPS);
  EXPECT_NEAR(stats.overpayment_on_credit, 21875, EPS);
}
