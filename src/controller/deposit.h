// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_CONTROLLER_DEPOSIT_H_
#define SRC_SRC_CONTROLLER_DEPOSIT_H_

#include <model.h>

namespace ns {
class DepositController {
 public:
  class DepositConditions {
   public:
    typedef enum { MONTH, QUARTAL, YEAR } PayingPeriod;

   private:
    double deposit_;                      // сумма вклада
    int months_;                          // срок размещения
    double percent_;                      // процентная ставка
    double tax_;                          // налоговая ставка
    PayingPeriod capitalization_period_;  // периодичность выплат
    bool percent_capitalization_;  // капитализация процентов
    double monthly_deposit_;       // сумма пополнений
    double monthly_withdrawal_;  // сумма частичных снятий

    bool yearly_;

   public:
    DepositConditions(double deposit, int months, double percent,
                      PayingPeriod capitalization_period,
                      bool percent_capitalization, double monthly_deposit,
                      double monthly_withdrawal, bool yearly,
                      double tax = defaultTaxPercent);

    bool Validate();

    operator Deposit::DepositConditions() const;
  };

 private:
  DepositConditions conditions_;

  typedef struct DepositStats {
    float earnings;
    float tax;
    float total;

    DepositStats(Deposit::DepositStats);
  } DepositStats;

  constexpr static const double defaultTaxPercent = 0;

 public:
  DepositController(DepositConditions conditions) : conditions_(conditions) {}
  DepositStats Calculate();
};
}  // namespace ns

#endif  //  SRC_SRC_CONTROLLER_DEPOSIT_H_
