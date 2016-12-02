#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QtWidgets>
#include <QTableWidget>
#include "abstractanalysewidget.h"

class StatAnalyseWidget : public AbstractAnalyseWidget
{
    Q_OBJECT
public:
    explicit StatAnalyseWidget(QWidget *parent = 0);


public Q_SLOTS:
    void analysisStarted() override;
    void analysisUpdated(const Sequence &sequence) override;
    void analysisFinished() override;



private:
    QPlainTextEdit * mEdit;
    bool done = false;


};

#endif // STATISTICSWIDGET_H
