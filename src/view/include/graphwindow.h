// Copyright 2024 EnergoStalin. All Rights Reserved.
#ifndef SRC_SRC_VIEW_INCLUDE_GRAPHWINDOW_H_
#define SRC_SRC_VIEW_INCLUDE_GRAPHWINDOW_H_

#include <QDialog>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class GraphWindow;
}
QT_END_NAMESPACE

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr);
  void on_to_draw_button_clicked(std::string);

  ~GraphWindow();

 public slots:

  void on_redraw();

 private:
  Ui::GraphWindow *ui_;
  std::string line_;
};

#endif  //  SRC_SRC_VIEW_INCLUDE_GRAPHWINDOW_H_
