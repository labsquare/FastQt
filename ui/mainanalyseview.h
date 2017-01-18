#ifndef MAINANALYSEVIEW_H
#define MAINANALYSEVIEW_H
#include <QTableView>
#include <QtWidgets>
#include "mainanalysemodel.h"

class MainAnalyseView;
class MainAnalyseDelegate;


class MainAnalyseDelegate : public QStyledItemDelegate
{
public:
void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

//================================================

class MainAnalyseView : public QTableView
{
public:
    MainAnalyseView(QWidget * parent = Q_NULLPTR);
    void addFile(const QString& filename);


private:
    MainAnalyseModel * mModel;
    MainAnalyseDelegate * mDelegate;
};

#endif // MAINANALYSEVIEW_H
