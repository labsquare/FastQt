#ifndef PERBASEQUALITYANALYSIS_H
#define PERBASEQUALITYANALYSIS_H

#include <QtCharts>
#include "analysis.h"

using namespace QT_CHARTS_NAMESPACE;

class QualityCount;
class PerBaseQualityAnalysis : public Analysis
{
public:
    PerBaseQualityAnalysis();

    virtual void processSequence(const Sequence& sequence) override;
    virtual void reset() override;
    virtual QWidget* createResultWidget() override;


protected:
    qreal findMedian(int begin, int end);


private:
    QVector<qreal> means;
    QVector<qreal> medians;
    QVector<qreal> lowerQuartile;
    QVector<qreal> upperQuartile;
    QVector<qreal> lowest;
    QVector<qreal> highest;

    QList<QualityCount> mQualityCounts;

    QList<qreal> sortedList = {1,4,5,6,4,2,5,6,4,2,6,2,5,4,2,5,2,2,4,5,2,4,2,10,20,10,4,5,4};

};


class QualityCount {

public:
    QualityCount();
    void addValue(char c);
    qreal mean();
    char min();
    char max();
    qreal percentile(int percentile);



private:
    QHash<char,int> mCounts;
    int mTotalCounts;
};




#endif // PERBASEQUALITYANALYSIS_H
