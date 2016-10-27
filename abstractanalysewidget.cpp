#include "abstractanalysewidget.h"

AbstractAnalyseWidget::AbstractAnalyseWidget(FastqReader * reader,QWidget *parent)
    : QWidget(parent)
{
    mReader = reader;
}

const FastqReader *AbstractAnalyseWidget::reader() const
{
    return mReader;
}
