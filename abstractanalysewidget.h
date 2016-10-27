#ifndef ABSTRACTANALYSEWIDGET_H
#define ABSTRACTANALYSEWIDGET_H

#include <QWidget>
#include "fastqreader.h"

class AbstractAnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractAnalyseWidget(FastqReader * reader, QWidget *parent = 0);


    const FastqReader * reader() const;

private:
    FastqReader * mReader;


};

#endif // ABSTRACTANALYSEWIDGET_H
