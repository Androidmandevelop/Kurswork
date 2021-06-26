#ifndef PROXYMODEL_HPP
#define PROXYMODEL_HPP

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT
public:
  ProxyModel(QObject* parent = nullptr);

protected:
  /**
   * @brief lessThan Сравнивает два значения по разным правилам относительно столбца для правильной сортировки
   * @param source_left Первое значение
   * @param source_right Второе значение
   * @return Возвращает true если первое значение больше второго, в противном случае - false
   */
  bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
};

#endif // PROXYMODEL_HPP
