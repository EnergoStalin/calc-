// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_CONTROLLER_CREDIT_H_
#define SRC_SRC_CONTROLLER_CREDIT_H_

#include <model.h>

namespace ns {
class CreditController {
 public:
  typedef enum { ANNUENT, DIFFERENTIAL } CreditType;

  typedef struct CreditStats {
    double first_monthly_payment;
    double last_monthly_payment;
    double overpayment_on_credit;
    double total_payment;

    CreditStats(ns::Credit::CreditStats s);
  } CreditStats;

  typedef struct CreditConditions {
    double total_credit_amount;
    int term;
    double interest_rate;
    CreditType type;

    CreditConditions(double total_credit_amount, int term, double interest_rate,
                     CreditType type, double yearly);

    bool Validate();
  } CreditConditions;

  CreditController(CreditConditions);

  CreditStats Calculate();

 private:
  CreditConditions conditions_;
};
}  // namespace ns

#endif  //  SRC_SRC_CONTROLLER_CREDIT_H_
