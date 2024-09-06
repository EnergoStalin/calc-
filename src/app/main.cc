// Copyright 2024 EnergoStalin. All Rights Reserved.
#include <creditwindow.h>
#include <depositwindow.h>
#include <mainwindow.h>

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow w;
  CreditWindow c;
  DepositWindow d;

  if (argc != 2) {
    w.show();
  } else if (strcmp(argv[1], "--credit") == 0) {
    c.show();
  } else if (strcmp(argv[1], "--deposit") == 0) {
    d.show();
  } else {
    std::cout << "Unknown argument: " << argv[1] << std::endl;
    exit(1);
  }

  return a.exec();
}
