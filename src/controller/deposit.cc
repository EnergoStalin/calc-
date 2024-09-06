#include "deposit.h"

#include <model.h>

#include <iostream>

ns::DepositController::DepositStats ns::DepositController::Calculate() {
  return ns::DepositController::DepositStats(
      ns::Deposit(conditions_).Stats());
}

ns::DepositController::DepositConditions::DepositConditions(
    double deposit, int months, double percent,
    PayingPeriod capitalization_period, bool percent_capitalization,
    double monthly_deposit, double monthly_withdrawal, bool yearly, double tax)
    : deposit_(deposit),
      months_(months),
      percent_(percent),
      tax_(tax),
      capitalization_period_(capitalization_period),
      percent_capitalization_(percent_capitalization),
      monthly_deposit_(monthly_deposit),
      monthly_withdrawal_(monthly_withdrawal) {
  if (yearly) {
    months_ *= 12;
  }
}

bool ns::DepositController::DepositConditions::Validate() {
  return months_ > 0 && percent_ >= 0.01;
}

ns::DepositController::DepositConditions::operator ns::Deposit::
    DepositConditions() const {
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "Deposit: " << deposit_ << std::endl;
  std::cout << "Months: " << months_ << std::endl;
  std::cout << "Percent: " << percent_ << std::endl;
  std::cout << "Monthly deposit: " << monthly_deposit_ << std::endl;
  std::cout << "Monthly withdrawal: " << monthly_withdrawal_ << std::endl;
  std::cout << "Capitalization: " << capitalization_period_ << std::endl;
  std::cout << "Tax: " << tax_ << std::endl;
  std::cout << "--------------------------------------------" << std::endl;

  return ns::Deposit::DepositConditions(
      deposit_, months_, percent_,
      static_cast<ns::Deposit::DepositConditions::PayingPeriod>(
          capitalization_period_),
      monthly_deposit_, monthly_withdrawal_, tax_);
}

ns::DepositController::DepositStats::DepositStats(
    Deposit::DepositStats deposit)
    : earnings(deposit.percents), tax(deposit.tax), total(deposit.sum) {
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "Earnings: " << earnings << std::endl;
  std::cout << "Tax: " << tax << std::endl;
  std::cout << "Total: " << total << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
}
