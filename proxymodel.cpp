#include "proxymodel.hpp"

ProxyModel::ProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

bool ProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
  QString left = sourceModel()->data(source_left).toString();
  QString right = sourceModel()->data(source_right).toString();

  if ((source_left.column() >= 4 && source_left.column() <= 10) || source_left.column() == 12)
    return left.toInt() < right .toInt();

  if (source_left.column() == 11)
    return left.toDouble() < right .toDouble();

  return QString::localeAwareCompare(left, right ) < 0;
}
