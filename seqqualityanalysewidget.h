#ifndef SEQQUALITYANALYSEWIDGET_H
#define SEQQUALITYANALYSEWIDGET_H
#include <QtWidgets>
#include "abstractanalysewidget.h"
class SeqQualityAnalyseWidget : public AbstractAnalyseWidget
{
public:
    SeqQualityAnalyseWidget(FastqReader * reader, QWidget * parent = 0);
};

#endif // SEQQUALITYANALYSEWIDGET_H
