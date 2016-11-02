#ifndef SEQQUALITYANALYSEWIDGET_H
#define SEQQUALITYANALYSEWIDGET_H
#include <QtWidgets>
#include "abstractanalysewidget.h"
class SeqQualityAnalyseWidget : public AbstractAnalyseWidget
{
public:
    SeqQualityAnalyseWidget(FastqProcess * reader, QWidget * parent = 0);

public slots:
    void fill() Q_DECL_OVERRIDE;
};

#endif // SEQQUALITYANALYSEWIDGET_H
