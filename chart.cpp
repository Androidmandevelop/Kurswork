#include "chart.hpp"
#include "ui_chart.h"

#include <QtCharts>


Chart::Chart(QList<Plotter> table, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Chart),
  Table(table)
{
  ui->setupUi(this);
  resize(1000, 700);
}

Chart::~Chart()
{
  delete ui;
}

void Chart::Price()
{
  QBarSet* plotterBarSet[Table.size()];
  QBarSeries* series = new QBarSeries();

  for (int i = 0; i < Table.size(); ++i)
  {
      plotterBarSet[i] = new QBarSet(QString::fromStdString(Table[i].getManufacturer() + ' ' +
                                                             Table[i].getModel()));
      int number = 0;
      number = Table[i].getPrice();
      *plotterBarSet[i] << number;
      series->append(plotterBarSet[i]);
  }

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle(tr("Prices"));

  chart->setAnimationOptions(QChart::SeriesAnimations);

  QBarCategoryAxis* axisX = new QBarCategoryAxis();
  axisX->append("");
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis* axisY = new QValueAxis();
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignRight);

  QChartView* chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(chartView);

  QWidget* price = new QWidget;
  price->setLayout(layout);

  ui->gridLayout->addWidget(price);
}

void Chart::SpeedPrint()
{
  QBarSet* plotterBarSet[Table.size()];
  QBarSeries* series = new QBarSeries();

  for (int i = 0; i < Table.size(); ++i)
  {
      plotterBarSet[i] = new QBarSet(QString::fromStdString(Table[i].getManufacturer() + ' ' +
                                                             Table[i].getModel()));
      int number = 0;
      number = Table[i].getProperties().SPEED_PRINT;
      *plotterBarSet[i] << number;
      series->append(plotterBarSet[i]);
  }

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle(tr("Speed of Print"));

  chart->setAnimationOptions(QChart::SeriesAnimations);

  QBarCategoryAxis* axisX = new QBarCategoryAxis();
  axisX->append("");
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis* axisY = new QValueAxis();
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignRight);

  QChartView* chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(chartView);

  QWidget* price = new QWidget;
  price->setLayout(layout);

  ui->gridLayout->addWidget(price);
}
