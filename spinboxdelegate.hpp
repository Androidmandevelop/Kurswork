#ifndef SPINBOXDELEGATE_HPP
#define SPINBOXDELEGATE_HPP

#include <QStyledItemDelegate>


class SpinBoxDelegate : public QStyledItemDelegate
{
  int column;
public:
  explicit SpinBoxDelegate(int column, QWidget *parent = nullptr);

  /**
   * @brief createEditor Создание SpinBox или DoubleSpinBox редактора в зависимости от столбца
   */
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

  /**
   * @brief setEditorData Задание значения из таблицы в редактор
   */
  void setEditorData(QWidget *editor, const QModelIndex &index) const;

  /**
   * @brief setModelData Задает значение из редактора в ячейку таблицы
   */
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

  /**
   * @brief updateEditorGeometry Обновляет размер редактора по размеру ячейки
   */
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SPINBOXDELEGATE_HPP
