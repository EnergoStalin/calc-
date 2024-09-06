// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_MODEL_DEPOSIT_H_
#define SRC_SRC_MODEL_DEPOSIT_H_

namespace ns {
class Deposit {
 public:
  typedef struct DepositConditions {
    typedef enum { NONE, MONTH, QUARTAL, YEAR } PayingPeriod;

    double deposit;
    int months;
    double percent;
    double monthly_deposit;
    double monthly_withdrawal;
    PayingPeriod capitalization_period;
    double tax;

    DepositConditions(double deposit, int months, double percent,
                      PayingPeriod capitalization_period,
                      double monthly_deposit, double monthly_withdrawal,
                      double tax);
    DepositConditions(double deposit, int months, double percent);
    DepositConditions(double deposit, int months, double percent, double tax);
    DepositConditions(double deposit, int months, double percent,
                      double monthly_deposit, double monthly_withdrawal,
                      double tax);
    DepositConditions(double deposit, int months, double percent,
                      PayingPeriod capitalization_period, double tax);

    bool Validate();
    bool capitalization() const;
  } DepositConditions;

  typedef struct DepositStats {
    double percents;  // начисленные проценты
    double tax;       // сумма налога
    double sum;       // сумма на вкладе к концу срока
  } DepositStats;

  Deposit(DepositConditions conditions);
  DepositStats Stats();

 private:
  DepositConditions conditions_;

  int period_;
  int divisor_;
};
};  // namespace ns

#endif /* SRC_CALC_INCLUDE_DEPOSIT_H_ */
