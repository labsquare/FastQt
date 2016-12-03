#ifndef PERBASEQUALITYANALYSIS_H
#define PERBASEQUALITYANALYSIS_H

#include <QtCharts>
#include "analysis.h"
#include "basegroup.h"

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
    qreal mean(int minbp, int maxbp);
    qreal percentile(int minbp, int maxbp, int percentile);
    void computePercentages();


private:
    QVector<qreal> means;
    QVector<qreal> medians;
    QVector<qreal> lowerQuartile;
    QVector<qreal> upperQuartile;
    QVector<qreal> lowest;
    QVector<qreal> highest;
   QVector<QString> xLabels;

    QList<QualityCount> mQualityCounts;

    QList<qreal> sortedList = {1,4,5,6,4,2,5,6,4,2,6,2,5,4,2,5,2,2,4,5,2,4,2,10,20,10,4,5,4};

};


class QualityCount {

public:
    QualityCount();
    void addValue(char c);
    qreal mean()const;
    char min()const;
    char max()const;
    qreal percentile(int percentile)const;
    int count() const;



private:
    QHash<char,int> mCounts;
    int mTotalCounts;
};




#endif // PERBASEQUALITYANALYSIS_H
