// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_MODEL_CREDIT_H_
#define SRC_SRC_MODEL_CREDIT_H_

namespace ns {
class Credit {
 public:
  typedef enum { ANNUENT, DIFFERENTIAL } CreditType;

  typedef struct CreditStats {
    double first_monthly_payment;
    double last_monthly_payment;
    double overpayment_on_credit;
    double total_payment;
  } CreditStats;

  Credit(double total_credit_amount, int term, double interest_rate,
         CreditType type);

  CreditStats Stats();

 private:
  double total_credit_amount_;  // общая сумма кредита
  int term_;                    // срок в месяцах
  double interest_rate_;        // процентная ставка
  CreditType type_;  // тип (годовой, дифференцированный)
};
}  // namespace ns

#endif /* SRC_CALC_INCLUDE_CREDIT_H_ */
