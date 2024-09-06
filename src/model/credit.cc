#include "credit.h"

#include <math.h>

ns::Credit::Credit(double total_credit_amount, int term, double interest_rate,
                    CreditType type)
    : total_credit_amount_(total_credit_amount),
      term_(term),
      interest_rate_(interest_rate),
      type_(type) {}

ns::Credit::CreditStats ns::Credit::Stats() {
  CreditStats c;

  if (type_ == ANNUENT) {
    interest_rate_ /= 1200;

    double temp = pow(1 + interest_rate_, term_);
    c.first_monthly_payment =
        (total_credit_amount_ * interest_rate_ * temp) / (temp - 1);

    c.total_payment = c.first_monthly_payment * term_;
    c.overpayment_on_credit = c.total_payment - total_credit_amount_;
  } else {
    double month_pay = total_credit_amount_ / term_;
    double temp = total_credit_amount_;
    double first_month =
        month_pay +
        round((total_credit_amount_ * interest_rate_ / 100 / 12) * 100) / 100;
    double sum_payd = first_month;

    double last_month = 0;
    for (int i = 1; i < term_; ++i) {
      total_credit_amount_ -= month_pay;
      last_month = round((month_pay +
                          ((total_credit_amount_)*interest_rate_ / 100 / 12)) *
                         100) /
                   100;

      sum_payd = round((sum_payd + last_month) * 100) / 100;
    }

    c.first_monthly_payment = first_month;
    c.last_monthly_payment = last_month;
    c.overpayment_on_credit = sum_payd - temp;
    c.total_payment = sum_payd;
  }

  return c;
}
