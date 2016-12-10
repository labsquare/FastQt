#include "keyvaluemodel.h"


KeyValueModel::KeyValueModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void KeyValueModel::addValue(const QString &label, const QVariant &value, const QString &description)
{
    beginResetModel();
    mDatas.insert(label, value);
    mDescriptions.insert(label, description);
    endResetModel();

}

int KeyValueModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

int KeyValueModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mDatas.count();
}

QVariant KeyValueModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    QString key = mDatas.keys().at(index.row());

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return key;

        if (index.column() == 1)
            return mDatas.value(key);
    }


    if ( role == Qt::ToolTipRole)
        return mDescriptions.value(key);

    return QVariant();

}
