#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include "plotter.hpp"

class TableModel : public QAbstractTableModel
{
  Q_OBJECT

private:
  /**
   * @brief dataList Хранилище данных таблицы
   */
  QList<Plotter> dataList;
  /**
   * @brief columns Кол-во столбцов
   */
  int columns;

signals:
  /**
   * @brief wasModified - сигнал об изменении данных в таблице
   */
  void wasModified();

public:
  TableModel(QObject* parent = nullptr);

  /**
   * @brief rowCount Возвращает количество строк
   */
  int rowCount(const QModelIndex &parent) const;
  /**
   * @brief columnCount Возвращает количество столбцов
   */
  int columnCount(const QModelIndex &parent) const;
  /**
   * @brief data Отображает значения хранилища данных в зависимости от роли
   */
  QVariant data(const QModelIndex &index, int role) const;
  /**
   * @brief setData Задает значение нужной ячейки
   * @param value Задаваемое значение
   */
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  /**
   * @brief flags Поддерживаемы флаги
   */
  Qt::ItemFlags flags(const QModelIndex &index) const;
  /**
   * @brief headerData Вывод заголовков
   */
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /**
   * @brief clear Удаляет все из хранилища данных
   */
  void clear();
  /**
   * @brief insertValue Добавление новой записи в конец таблицы
   * @param value Добавленное значение
   */
  void insertValue(const Plotter &value);
  /**
   * @brief insertRows Вставляет новое значение
   */
  bool insertRows(int row, int count, const QModelIndex &parent);
  /**
   * @brief removeRows Удаляет выбранное значение
   */
  bool removeRows(int row, int count, const QModelIndex &parent);
  /**
   * @brief getQList Получение данных в формате QList
   */
  QList<Plotter> getQList() const {return dataList;}
};

#endif // TABLEMODEL_HPP
