// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_VIEW_INCLUDE_MAINWINDOW_H_
#define SRC_SRC_VIEW_INCLUDE_MAINWINDOW_H_

#include <QMainWindow>

#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  GraphWindow *window2;

 private slots:
  void digit_numbers();
  void on_pushButton_TOCHKA_clicked();
  void on_pushButton_EQUAL_clicked();
  void operations();
  void functions();
  void on_pushButton_DELETE_clicked();
  void on_pushButton_X_clicked();
};

#endif  //  SRC_SRC_VIEW_INCLUDE_MAINWINDOW_H_
