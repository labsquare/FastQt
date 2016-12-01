#ifndef ABSTRACTANALYSEWIDGET_H
#define ABSTRACTANALYSEWIDGET_H

#include <QWidget>
#include "sequence.h"
class AbstractAnalyseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractAnalyseWidget(QWidget *parent = 0);

public Q_SLOTS:
    virtual void analysisStarted(){}
    virtual void analysisUpdated(const Sequence& sequence){}
    virtual void analysisFinished(){}





};

#endif // ABSTRACTANALYSEWIDGET_H
