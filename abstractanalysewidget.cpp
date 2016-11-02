#include "abstractanalysewidget.h"

AbstractAnalyseWidget::AbstractAnalyseWidget(FastqProcess * reader,QWidget *parent)
    : QWidget(parent)
{
    mReader = reader;

    connect(mReader, &FastqProcess::done, this, &AbstractAnalyseWidget::fill);
}

const FastqProcess *AbstractAnalyseWidget::reader() const
{
    return mReader;
}
