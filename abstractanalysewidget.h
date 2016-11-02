#ifndef ABSTRACTANALYSEWIDGET_H
#define ABSTRACTANALYSEWIDGET_H

#include <QWidget>
#include "fastqprocess.h"

class AbstractAnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractAnalyseWidget(FastqProcess * reader, QWidget *parent = 0);
    const FastqProcess * reader() const;

public Q_SLOTS:
    virtual void fill() = 0;

private:
    FastqProcess * mReader;


};

#endif // ABSTRACTANALYSEWIDGET_H
