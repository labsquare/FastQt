#ifndef PERBASECONTENTANALYSIS_H
#define PERBASECONTENTANALYSIS_H
#include <QtCore>
#include <QtCharts>
#include "analysis.h"
#include "basegroup.h"

using namespace QT_CHARTS_NAMESPACE;

class PerBaseContentAnalysis : public Analysis
{
public:
    PerBaseContentAnalysis();

    virtual void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual QWidget* createResultWidget() Q_DECL_OVERRIDE;

protected:
    void computePercentages();

private:
    QVector<quint64> mGCounts;
    QVector<quint64> mACounts;
    QVector<quint64> mCCounts;
    QVector<quint64> mTCounts;
    QVector<quint64> mXCounts;

    QVector<qreal> gPercent;
    QVector<qreal> aPercent;
    QVector<qreal> tPercent;
    QVector<qreal> cPercent;

    QVector<QString> mXCategories;
    QVector<quint64>* counts[256];
};

#endif // PERBASECONTENTANALYSIS_H
