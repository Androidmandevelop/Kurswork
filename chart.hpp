#ifndef CHART_HPP
#define CHART_HPP

#include <QWidget>
#include "plotter.hpp"

namespace Ui {
  class Chart;
}

class Chart : public QWidget
{
  Q_OBJECT

public:
  explicit Chart(QList<Plotter> table, QWidget *parent = nullptr);
  ~Chart();

  void Price();

  void SpeedPrint();

private:
  Ui::Chart *ui;

  QList<Plotter> Table;
};

#endif // CHART_HPP
