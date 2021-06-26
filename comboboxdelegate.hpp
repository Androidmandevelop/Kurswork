#ifndef COMBOBOXDELEGATE_HPP
#define COMBOBOXDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QVector>

class ComboBoxDelegate : public QStyledItemDelegate
{
  Q_OBJECT

  QVector<QString> items;
  int column;

public:
  ComboBoxDelegate(int col, QWidget *parent = nullptr);

  /**
   * @brief createEditor Создание CheckBox редактора
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
};

#endif // COMBOBOXDELEGATE_HPP
