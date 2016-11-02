#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QtWidgets>
#include <QTableWidget>
#include "abstractanalysewidget.h"
#include "fastqprocess.h"

class StatAnalyseWidget : public AbstractAnalyseWidget
{
    Q_OBJECT
public:
    explicit StatAnalyseWidget(FastqProcess * reader, QWidget *parent = 0);

public slots:
    void fill() Q_DECL_OVERRIDE;

protected:
    void addField(const QString& label, const QString& value);


private:
    QTreeWidget * mView;


};

#endif // STATISTICSWIDGET_H
