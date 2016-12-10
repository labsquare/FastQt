#ifndef PERSEQUENCEQUALITYANALYSIS_H
#define PERSEQUENCEQUALITYANALYSIS_H

#include <QtCore>
#include <QtCharts>
#include "analysis.h"

using namespace QT_CHARTS_NAMESPACE;

class PerSequenceQualityAnalysis : public Analysis
{
public:
    PerSequenceQualityAnalysis();

    virtual void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual QWidget* createResultWidget()Q_DECL_OVERRIDE;


private:
QHash<int, quint64> mAverageScoreCounts;

};

#endif // PERSEQUENCEQUALITYANALYSIS_H
