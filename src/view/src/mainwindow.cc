#include "mainwindow.h"

#include <controller.h>

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QShortcut>
#include <QString>
#include <stdexcept>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  window2 = new GraphWindow(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(on_pushButton_DELETE_clicked()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(on_pushButton_X_clicked()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(on_pushButton_TOCHKA_clicked()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this,
          SLOT(on_pushButton_EQUAL_clicked()));

  auto shortcut = new QShortcut(QKeySequence("="), this);
  connect(shortcut, SIGNAL(activated()), this,
          SLOT(on_pushButton_EQUAL_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_numbers() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());

  QString label = ui->plainTextEdit->toPlainText() + button->text();

  ui->plainTextEdit->setPlainText(label);
}

void MainWindow::operations() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());

  QString label = ui->plainTextEdit->toPlainText();
  QString append = button->text();

  if (!label.endsWith(append)) {
    label += append;
  }

  ui->plainTextEdit->setPlainText(label);
}

void MainWindow::functions() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());

  QString label = ui->plainTextEdit->toPlainText() + button->text() + "(";
  ui->plainTextEdit->setPlainText(label);
}

void MainWindow::on_pushButton_DELETE_clicked() {
  ui->plainTextEdit->setPlainText("");
}

void MainWindow::on_pushButton_X_clicked() {
  QString label;

  if (!(ui->plainTextEdit->toPlainText().endsWith("x")))
    label = ui->plainTextEdit->toPlainText() + "x";

  ui->plainTextEdit->setPlainText(label);
}
void MainWindow::on_pushButton_TOCHKA_clicked() {
  if (!(ui->plainTextEdit->toPlainText().endsWith('.')))
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + ".");
}

void MainWindow::on_pushButton_EQUAL_clicked() {
  ns::CalculatorController c;
  QByteArray ba = ui->plainTextEdit->toPlainText().toLatin1();
  char *str = ba.data();

  try {
    if (ui->plainTextEdit->toPlainText().contains("x")) {
      window2->on_to_draw_button_clicked(str);
      window2->show();
    } else {
      ui->plainTextEdit->setPlainText(
          QString::number(c.EvaluateExpression(str)));
    }
  } catch (const std::invalid_argument &e) {
    ui->plainTextEdit->setPlainText(e.what());
  }
}
