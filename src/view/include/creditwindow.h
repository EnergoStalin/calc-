// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_VIEW_INCLUDE_CREDITWINDOW_H_
#define SRC_SRC_VIEW_INCLUDE_CREDITWINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CreditWindow;
}
QT_END_NAMESPACE

class CreditWindow : public QMainWindow {
  Q_OBJECT

 public:
  CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private:
  Ui::CreditWindow *ui_;

 private slots:

  void Calculate();
};

#endif  //  SRC_SRC_VIEW_INCLUDE_CREDITWINDOW_H_
