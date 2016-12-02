#ifndef BASICSTATSANALYSIS_H
#define BASICSTATSANALYSIS_H
#include <QtCore>
#include <QLocale>
#include "analysis.h"
#include  "keyvaluemodel.h"

class BasicStatsAnalysis : public Analysis
{
public:
    BasicStatsAnalysis();
    void processSequence(const Sequence& sequence) override;
    void reset() override;
    QWidget * createResultWidget() override;

private:
    QString mEncoding;
    int mReadCount;
    int mMinLength;
    int mMaxLength;



};

#endif // BASICSTATSANALYSIS_H
