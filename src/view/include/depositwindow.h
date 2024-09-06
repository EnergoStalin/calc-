// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_VIEW_INCLUDE_DEPOSITWINDOW_H_
#define SRC_SRC_VIEW_INCLUDE_DEPOSITWINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DepositWindow;
}
QT_END_NAMESPACE

class DepositWindow : public QMainWindow {
  Q_OBJECT

 public:
  DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();

 private:
  Ui::DepositWindow *ui_;

 private slots:
  void Calculate();
};

#endif  //  SRC_SRC_VIEW_INCLUDE_DEPOSITWINDOW_H_
