#ifndef TABLEVIEW_HPP
#define TABLEVIEW_HPP

#include <QTableView>

class TableView : public QTableView
{
  Q_OBJECT
public:
  TableView(QWidget *parent = nullptr);

protected:
  /**
   * @brief mouseMoveEvent Переопределенный метод для drag&drop
   * @param event Принимающее событие
   */
  void mouseMoveEvent(QMouseEvent *event);
};

#endif // TABLEVIEW_HPP
