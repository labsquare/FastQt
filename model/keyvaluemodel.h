/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#ifndef KEYVALUEMODEL_H
#define KEYVALUEMODEL_H
#include <QAbstractListModel>
#include <QLocale>
/*!
 * \class KeyValueModel
 * \brief A simple key/model view
 * Display Key/value in a Table View. This class is used in BasicStatsAnalysis
 */
class KeyValueModel : public QAbstractListModel
{
public:
    KeyValueModel(QObject * parent = 0);

    void addValue(const QString& label, const QVariant& value, const QString& description = QString());



protected:
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QHash<QString, QVariant> mDatas;
    QHash<QString, QString> mDescriptions;


};

#endif // KEYVALUEMODEL_H
