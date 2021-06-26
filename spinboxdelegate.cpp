#include "spinboxdelegate.hpp"

#include <QSpinBox>
#include <QApplication>
#include <QAbstractItemView>

SpinBoxDelegate::SpinBoxDelegate(int column, QWidget *parent) :
  QStyledItemDelegate(parent), column(column)
{ }

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
  Q_UNUSED(option);
  Q_UNUSED(index);

  QSpinBox *editor = new QSpinBox(parent);

  switch (column) {
        case 4:
            {
            editor->setRange(80, 200);
            editor->setSingleStep(1);
            break;
            }
        case 5:
            {
            editor->setRange(500, 2000);
            editor->setSingleStep(50);
            break;
            }
        case 6:
            {
            editor->setRange(40000, 1000000);
            editor->setSingleStep(10000);
            editor->setSuffix(tr(" RUB"));
            break;
            }

   }

  return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
  QString strVal = index.model()->data(index, Qt::EditRole).toString();
  if (index.column() == 6)
      strVal.chop(3);
  int value = strVal.toInt();
  QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
  spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
  QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
  spinBox->interpretText();
  model->setData(index, spinBox->value(), Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
  Q_UNUSED(index);

  // Указываем, что используемое нами поле ввода должно находится
  // на месте той ячейке, которую мы редактируем
  editor->setGeometry(option.rect);
}
