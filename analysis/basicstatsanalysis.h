#ifndef BASICSTATSANALYSIS_H
#define BASICSTATSANALYSIS_H
#include <limits>
#include <QtCore>
#include <QLocale>
#include "analysis.h"
#include  "keyvaluemodel.h"
#include "phredencoding.h"

class BasicStatsAnalysis : public Analysis
{
public:
    BasicStatsAnalysis();
    void processSequence(const Sequence& sequence) override;
    void reset() override;
    QWidget * createResultWidget() override;

private:
    QString mEncoding;
    int mReadCount   = 0;
    int mMinLength   = std::numeric_limits<int>::max();
    int mMaxLength   = 0;
    quint64 mGCount  = 0;
    quint64 mCCount  = 0;
    quint64 mACount  = 0;
    quint64 mTCount  = 0;
    quint64 mNCount  = 0;
    quint64 mXCount  = 0;


    char mLowestChar = 126;
    quint64* count[256];
};

#endif // BASICSTATSANALYSIS_H
