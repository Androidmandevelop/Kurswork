#include "tableview.hpp"
#include "spinboxdelegate.hpp"
#include "comboboxdelegate.hpp"
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QApplication>

TableView::TableView(QWidget* parent) : QTableView(parent)
{
  setSortingEnabled(true);

  setSelectionBehavior(QAbstractItemView::SelectRows);

  setContextMenuPolicy(Qt::CustomContextMenu);

  setDragEnabled(true);
  setDropIndicatorShown(true);

  setItemDelegateForColumn(2, new ComboBoxDelegate(2, this));
  setItemDelegateForColumn(3, new ComboBoxDelegate(3, this));
  for (int i = 4; i <= 6; ++i)
    setItemDelegateForColumn(i, new SpinBoxDelegate(i, this));
}

void TableView::mouseMoveEvent(QMouseEvent *event)
{
  if (model()->rowCount() == 0)
    return;

  if (event->buttons() & Qt::LeftButton) {
      int distance = event->pos().manhattanLength();

      if (distance >= QApplication::startDragDistance()) {
          QModelIndex index = currentIndex();

          QString Manufacturer = index.siblingAtColumn(0).data().toString();
          QString Model = index.siblingAtColumn(1).data().toString();
          QString FormFactor = index.siblingAtColumn(2).data().toString();
          QString Format = index.siblingAtColumn(3).data().toString();
          QString SPEED_PRINT = index.siblingAtColumn(4).data().toString();
          QString Max_widht_print = index.siblingAtColumn(5).data().toString();
          QString Price = index.siblingAtColumn(6).data().toString();

          QString data =
              "Manufacturer: " + Manufacturer + "\n" +
              "Model: " + Model + "\n" +
              "Form-Factor: " + FormFactor + "\n" +
              "Format type: " + Format + "\n" +
              "\tSpeed print   " + SPEED_PRINT + "\n" +
              "\tMax_widht_print " + Max_widht_print + "\n" +
              "Price: " + Price + " RUB\n";

          QMimeData* mimeData = new QMimeData;
          mimeData->setText(data );

          QDrag *drag = new QDrag(this);
          drag->setMimeData(mimeData);
          drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        }
      QWidget::mouseMoveEvent(event);
    }
}
