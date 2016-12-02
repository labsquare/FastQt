#ifndef BASICSTATSANALYSIS_H
#define BASICSTATSANALYSIS_H
#include <QtCore>
#include "analysis.h"

class BasicStatsAnalysis : public Analysis
{
public:
    BasicStatsAnalysis();
    void processSequence(const Sequence& sequence) override;

    QWidget * createResultWidget() override;

private:
    int mTotal;


};

#endif // BASICSTATSANALYSIS_H
