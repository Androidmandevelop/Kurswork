#include "tablemodel.hpp"

TableModel::TableModel(QObject *parent) :
  QAbstractTableModel(parent), columns(7)
{ }

int TableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return dataList.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return columns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
      {
        const Plotter &item = dataList.at(index.row());

        if (index.column() == 0)
          return item.getManufacturer().c_str();
        else if (index.column() == 1)
          return item.getModel().c_str();
        else if (index.column() == 2)
          {
            const char *StrFormFactor[] = {"Default", "Jet", "Uneversal"};
            return StrFormFactor[item.getFormFactor()];
          }
        else if (index.column() == 3){
            const char *StrFormat[] = {"Default", "A0", "A1", "A2"};
            return StrFormat[item.getFormat()];
          }
        else if (index.column() == 4)
          return QString::number(item.getProperties().SPEED_PRINT);
        else if (index.column() == 5)
          return QString::number(item.getProperties().Max_widht_print);
        else if (index.column() == 6)
          return QString::number(item.getPrice()) + tr(" RUB");
        break;
      }
    default:
      return QVariant();
    }

  return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole) {
      Plotter item = dataList.at(index.row());

      switch (index.column()) {
        case 0:
          item.setManufacturer(value.toString().toStdString());
          break;
        case 1:
          item.setModel(value.toString().toStdString());
          break;
        case 2:
          {
            QString val = value.toString();
            QStringList StrFormFactor = {"Default", "Jet", "Uneversal"};
            auto FormFactor = static_cast<Plotter::EnumFormFactor>(StrFormFactor.indexOf(val));
            item.setFormFactor(FormFactor);
            break;
          }
        case 3:
          {
            QString val = value.toString();
            QStringList StrFormat = {"Default", "A0", "A1", "A2"};
            auto Format = static_cast<Plotter::EnumFormat>(StrFormat.indexOf(val));
            item.setFormat(Format);
            break;
          }
        case 4:
          {
            Plotter::Properties temp = item.getProperties();
            temp.SPEED_PRINT = value.toInt();
            item.setProperties(temp);
          }
          break;
        case 5:
          {
            Plotter::Properties temp = item.getProperties();
            temp.Max_widht_print = value.toInt();
            item.setProperties(temp);
          }
          break;
        case 6:
          item.setPrice(value.toInt());
          break;
        default:
          return false;
        }

      dataList.replace(index.row(), item);
      emit dataChanged(index, index);
      emit wasModified();

      return true;
    }

  return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
  if (index.isValid())
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
        | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
  else
    return Qt::NoItemFlags | Qt::ItemIsDropEnabled;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
      switch (section) {
        case 0:
          return tr("Manufacturer");
        case 1:
          return tr("Model");
        case 2:
          return tr("Type of plotter");
        case 3:
          return tr("Format type");
        case 4:
          return tr("Speed print");
        case 5:
          return tr("Max widht print");
        case 6:
          return tr("Price");
        }
    }
  return QVariant();
}

void TableModel::insertValue(const Plotter &value)
{
  dataList.push_back(value);
  emit layoutChanged();
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  beginInsertRows(QModelIndex(), row, row + count - 1);
  for (int i = 0; i < count; i++) {
      dataList.insert(row, Plotter());
    }
  emit wasModified();
  endInsertRows();
  return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  beginRemoveRows(QModelIndex(), row, row + count - 1);
  for (int i = 0; i < count; i++) {
      dataList.removeAt(row);
    }
  emit wasModified();
  endRemoveRows();
  return true;
}


void TableModel::clear()
{
  dataList.clear();
  emit layoutChanged();
}

