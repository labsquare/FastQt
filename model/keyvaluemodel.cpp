/*
Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

    FastQt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastQt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastQt.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
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
