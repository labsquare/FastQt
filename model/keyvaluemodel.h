#ifndef KEYVALUEMODEL_H
#define KEYVALUEMODEL_H
#include <QAbstractListModel>
#include <QLocale>

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
