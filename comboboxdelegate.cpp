#include "comboboxdelegate.hpp"
#include <QApplication>
#include <QComboBox>
#include <QString>

ComboBoxDelegate::ComboBoxDelegate(int col, QWidget *parent) :
  QStyledItemDelegate(parent), column(col)
{
  if (column == 2)
    {
      items.push_back("Default");
      items.push_back("Jet");
      items.push_back("Uneversal");
    }
  else if (column == 3)
    {
      items.push_back("Default");
      items.push_back("A0");
      items.push_back("A1");
      items.push_back("A2");
    }
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
  Q_UNUSED(option)
  Q_UNUSED(index)
  QComboBox* editor = new QComboBox(parent);
  for(int i = 0; i < items.size(); ++i)
    {
      editor->addItem(items[i]);
    }
  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
  QString currentText = index.data(Qt::EditRole).toString();
  int comboBoxIndex = comboBox->findText(currentText);

  if (comboBoxIndex >= 0)
    comboBox->setCurrentIndex(comboBoxIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}
