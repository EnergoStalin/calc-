// Copyright 2024 EnergoStalin. All Rights Reserved.
#include "creditwindow.h"

#include <credit.h>

#include "./ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::CreditWindow) {
  ui_->setupUi(this);

  connect(ui_->submit, SIGNAL(clicked()), this, SLOT(Calculate()));
}

void CreditWindow::Calculate() {
  auto period = ui_->period->value();

  ns::CreditController::CreditConditions ecc(
      ui_->sum->value(), period, ui_->percent->value(),
      ui_->annuient->isChecked() ? ns::CreditController::ANNUENT
                                 : ns::CreditController::DIFFERENTIAL,
      ui_->year->isChecked());

  if (ecc.Validate()) {
    auto c = ns::CreditController(ecc).Calculate();

    if (ui_->differential->isChecked()) {
      ui_->percent_income->setText(
          QString::number(c.overpayment_on_credit, 'f', 2));
      ui_->obligation_and_percent->setText(
          QString::number(c.total_payment, 'f', 2));
      ui_->monthly_pay->setText(
          QString::number(c.first_monthly_payment, 'f', 2) + "..." +
          QString::number(c.last_monthly_payment, 'f', 2));
    } else {
      ui_->monthly_pay->setText(
          QString::number(c.first_monthly_payment, 'g', 15));
      ui_->percent_income->setText(
          QString::number(c.overpayment_on_credit, 'g', 15));
      ui_->obligation_and_percent->setText(
          QString::number(c.total_payment, 'g', 15));
    }
  } else {
    ui_->monthly_pay->setText("The wrong settings gym");
    ui_->percent_income->setText("is");
    ui_->obligation_and_percent->setText("2 blocks down");
  }
}

CreditWindow::~CreditWindow() { delete ui_; }
