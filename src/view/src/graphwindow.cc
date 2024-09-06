#include "graphwindow.h"

#include <controller.h>
#include <qcustomplot.h>

#include "./ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget* parent)
    : QDialog(parent), ui_(new Ui::GraphWindow) {
  ui_->setupUi(this);

  connect(new QShortcut(QKeySequence("Ctrl+R"), this), SIGNAL(activated()),
          this, SLOT(on_redraw()));
}

GraphWindow::~GraphWindow() { delete ui_; }

void GraphWindow::on_to_draw_button_clicked(std::string line) {
  line_ = line;  // Save line for redraw

  ui_->widget->clearGraphs();

  double x_min_num = ui_->d_f_1->text().toDouble();
  double x_max_num = ui_->d_f_2->text().toDouble();

  double frequency = ui_->d_f_6->text().toDouble();

  ui_->widget->xAxis->setRange(x_min_num, x_max_num);
  ui_->widget->yAxis->setRange(x_min_num, x_max_num);

  auto c = ns::CalculatorController();

  auto d = c.GetGraphPoints(line_, x_min_num, x_max_num, frequency);

  auto x = QVector<double>(d.first.begin(), d.first.end());
  auto y = QVector<double>(d.second.begin(), d.second.end());

  ui_->widget->addGraph();
  ui_->widget->graph(0)->addData(x, y);

  ui_->widget->setInteraction(QCP::iRangeZoom, true);
  ui_->widget->setInteraction(QCP::iRangeDrag, true);

  ui_->widget->replot();
}

void GraphWindow::on_redraw() { GraphWindow::on_to_draw_button_clicked(line_); }
