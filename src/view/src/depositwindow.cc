#include "depositwindow.h"

#include <deposit.h>

#include "./ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::DepositWindow) {
  ui_->setupUi(this);

  ui_->comboBox->addItem("Ежемесячно");
  ui_->comboBox->addItem("Ежеквартально");
  ui_->comboBox->addItem("Ежегодно");

  connect(ui_->submit, SIGNAL(clicked()), this, SLOT(Calculate()));
}

void DepositWindow::Calculate() {
  double deposit = ui_->sum->value();
  int months = ui_->period->value();
  double percent = ui_->percent->value();
  auto capitalization_period =
      static_cast<ns::DepositController::DepositConditions::PayingPeriod>(
          ui_->comboBox->currentIndex());
  bool percent_capitalization = ui_->capitalization->isChecked();
  double monthly_deposit = ui_->incomings->value();
  double monthly_withdrawal = ui_->decrasings->value();
  bool yearly = ui_->year->isChecked();

  auto deposit_conditions = ns::DepositController::DepositConditions(
      deposit, months, percent, capitalization_period, percent_capitalization,
      monthly_deposit, monthly_withdrawal, yearly);

  if (deposit_conditions.Validate()) {
    auto d = ns::DepositController(deposit_conditions).Calculate();

    ui_->earnings->setText(QString::number(d.earnings, 'f', 2));
    ui_->tax->setText(QString::number(d.tax, 'f', 2));
    ui_->total->setText(QString::number(d.total, 'f', 2));
  } else {
    ui_->earnings->setText("The wrong settings gym");
    ui_->tax->setText("is");
    ui_->total->setText("2 blocks down");
  }
}

DepositWindow::~DepositWindow() { delete ui_; }
