#include "credit.h"

#include <model.h>

#include <iostream>

bool ns::CreditController::CreditConditions::Validate() {
  bool res = true;

  if (total_credit_amount <= 0) {
    res = false;
  } else if (term <= 0) {
    res = false;
  } else if (interest_rate <= 0) {
    res = false;
  } else if (type != ANNUENT && type != DIFFERENTIAL) {
    res = false;
  }

  return res;
}

ns::CreditController::CreditConditions::CreditConditions(
    double total_credit_amount, int term, double interest_rate, CreditType type,
    double yearly)
    : total_credit_amount(total_credit_amount),
      term(term),
      interest_rate(interest_rate),
      type(type) {
  if (yearly) {
    this->term *= 12;
  }

  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "Total credit amount: " << total_credit_amount << std::endl;
  std::cout << "Term: " << term << std::endl;
  std::cout << "Interest rate: " << interest_rate << std::endl;
  std::cout << "Type: " << type << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
}

ns::CreditController::CreditController(
    ns::CreditController::CreditConditions conditions)
    : conditions_(conditions) {}

ns::CreditController::CreditStats ns::CreditController::Calculate() {
  auto c = ns::Credit(conditions_.total_credit_amount, conditions_.term,
                       conditions_.interest_rate,
                       static_cast<ns::Credit::CreditType>(conditions_.type));
  return CreditStats(c.Stats());
}
ns::CreditController::CreditStats::CreditStats(ns::Credit::CreditStats s) {
  first_monthly_payment = s.first_monthly_payment;
  last_monthly_payment = s.last_monthly_payment;
  overpayment_on_credit = s.overpayment_on_credit;
  total_payment = s.total_payment;

  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "First monthly payment: " << s.first_monthly_payment
            << std::endl;
  std::cout << "Last monthly payment: " << s.last_monthly_payment << std::endl;
  std::cout << "Overpayment on credit: " << s.overpayment_on_credit
            << std::endl;
  std::cout << "Total payment: " << s.total_payment << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
}
