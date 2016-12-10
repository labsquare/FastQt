#ifndef PERBASEQUALITYANALYSIS_H
#define PERBASEQUALITYANALYSIS_H

#include <QtCharts>
#include "analysis.h"
#include "basegroup.h"
#include "phredencoding.h"

#define QUALITY_COUNT_SIZE 150

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
    qreal mean(int maxbp, int minbp, int offset);
    qreal percentile(int minbp, int offset, int maxbp,int percentile);
    void computePercentages();
    QPair<char,char> computeOffsets();


private:
    QVector<qreal> means;
    QVector<qreal> medians;
    QVector<qreal> lowerQuartile;
    QVector<qreal> upperQuartile;
    QVector<qreal> lowest;
    QVector<qreal> highest;
    QVector<QString> xLabels;
    QList<QualityCount> mQualityCounts;
    PhredEncoding mEncodingScheme;
    int mLow  = 0;
    int mHigh = 0;


};


class QualityCount {

public:
    QualityCount();
    void addValue(char c);
    qreal mean(int offset)const;
    char min()const;
    char max()const;
    qreal percentile(int offset,int percentile)const;
    int count() const;



private:
    // faster than QVector

    quint64 mCounts[QUALITY_COUNT_SIZE] = {0};
    int mTotalCounts     = 0;
};




#endif // PERBASEQUALITYANALYSIS_H
