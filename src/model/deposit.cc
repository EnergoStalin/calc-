#include "deposit.h"

ns::Deposit::Deposit(DepositConditions conditions)
    : conditions_(conditions), period_(12), divisor_(1) {
  switch (conditions_.capitalization_period) {
    case DepositConditions::MONTH:
      period_ = 12;
      divisor_ = 1;
      break;
    case DepositConditions::QUARTAL:
      period_ = 4;
      divisor_ = 3;
      break;
    case DepositConditions::YEAR:
      period_ = 1;
      divisor_ = 12;
      break;
    case DepositConditions::NONE:
      break;
  }
}

ns::Deposit::DepositStats ns::Deposit::Stats() {
  DepositStats d;

  double tax_rate = conditions_.tax / 1000;
  double key_rate = 0.0425;
  double exempted_income = 1000000 * key_rate;

  double interest = 0.0;
  double total_interest = 0.0;
  double final_amount = conditions_.deposit;

  if (conditions_.capitalization()) {
    conditions_.percent /= 100;
    double principal = conditions_.deposit;

    for (int i = 0; i < conditions_.months / divisor_; ++i) {
      double monthly_interest = (principal * conditions_.percent / period_) +
                                conditions_.monthly_deposit -
                                conditions_.monthly_withdrawal;
      principal += monthly_interest;
      total_interest += monthly_interest;
    }
    interest = total_interest;
    final_amount += total_interest;
  } else {
    interest =
        ((conditions_.deposit * conditions_.percent * conditions_.months) /
         (100 * period_)) /
        divisor_;
    final_amount += (conditions_.monthly_deposit * period_);
    final_amount -= (conditions_.monthly_withdrawal * period_);
  }

  double taxable_income = interest - exempted_income;
  if (taxable_income < 0) {
    taxable_income = 0;
  }

  double tax = taxable_income * tax_rate;
  double final_interest = interest - tax;

  if (conditions_.capitalization()) {
    final_amount -= tax;
  }

  d.sum = final_amount;
  d.percents = final_interest;
  d.tax = tax;

  return d;
}

ns::Deposit::DepositConditions::DepositConditions(
    double deposit, int months, double percent,
    PayingPeriod capitalization_period, double monthly_deposit,
    double monthly_withdrawal, double tax)
    : deposit(deposit),
      months(months),
      percent(percent),
      monthly_deposit(monthly_deposit),
      monthly_withdrawal(monthly_withdrawal),
      capitalization_period(capitalization_period),
      tax(tax) {}
ns::Deposit::DepositConditions::DepositConditions(double deposit, int months,
                                                   double percent)
    : DepositConditions(deposit, months, percent, NONE, 0, 0, 0) {}
ns::Deposit::DepositConditions::DepositConditions(double deposit, int months,
                                                   double percent, double tax)
    : DepositConditions(deposit, months, percent, NONE, 0, 0, tax) {}
ns::Deposit::DepositConditions::DepositConditions(double deposit, int months,
                                                   double percent,
                                                   double monthly_deposit,
                                                   double monthly_withdrawal,
                                                   double tax)
    : DepositConditions(deposit, months, percent, NONE, monthly_deposit,
                        monthly_withdrawal, tax) {}
ns::Deposit::DepositConditions::DepositConditions(
    double deposit, int months, double percent,
    PayingPeriod capitalization_period, double tax)
    : DepositConditions(deposit, months, percent, capitalization_period, 0, 0,
                        tax) {}

bool ns::Deposit::DepositConditions::Validate() {
  return deposit > 0 && months > 0 && percent >= 0 && monthly_deposit >= 0 &&
         monthly_withdrawal >= 0 && tax >= 0;
}
bool ns::Deposit::DepositConditions::capitalization() const {
  return capitalization_period != NONE;
}
