#include "perbasequalityanalysis.h"

PerBaseQualityAnalysis::PerBaseQualityAnalysis()
{
    setName("PerBase analysis");
}

void PerBaseQualityAnalysis::processSequence(const Sequence &sequence)
{



    if ( mQualityCounts.size() < sequence.quality().size())
    {

        for (int i= mQualityCounts.size(); i<sequence.quality().size(); ++i)
            mQualityCounts.append(QualityCount());

    }


    for (int i=0; i< sequence.quality().size(); ++i)
        mQualityCounts[i].addValue(sequence.quality()[i]);



}

void PerBaseQualityAnalysis::reset()
{
    mQualityCounts.clear();
}

QWidget *PerBaseQualityAnalysis::createResultWidget()
{

    computePercentages();

    QBoxPlotSeries *qualSerie = new QBoxPlotSeries();

    for (int i=0; i<means.size(); ++i)
    {
        QBoxSet *box = new QBoxSet(xLabels[i]);
        box->setValue(QBoxSet::LowerExtreme, lowest[i]);
        box->setValue(QBoxSet::UpperExtreme, highest[i]);
        box->setValue(QBoxSet::Median, medians[i]);
        box->setValue(QBoxSet::LowerQuartile,lowerQuartile[i]);
        box->setValue(QBoxSet::UpperQuartile, upperQuartile[i]);

        qualSerie->append(box);

    }


    QChart * chart = new QChart();
    chart->addSeries(qualSerie);

    chart->setTitle("Quality per base");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();

    QChartView * view = new QChartView;
    view->setChart(chart);

    return view;

}

qreal PerBaseQualityAnalysis::mean(int minbp, int maxbp)
{
    int count    = 0;
    double total = 0;

    for (int i=minbp-1;i<maxbp;i++) {
        if (mQualityCounts[i].count() > 0) {
            count++;
            total += mQualityCounts[i].mean();
        }
    }

    if (count > 0) {
        return total/count;
    }
    return 0;


}

qreal PerBaseQualityAnalysis::percentile(int minbp, int maxbp, int percentile)
{
    int count = 0;
    double total = 0;

    for (int i=minbp-1;i<maxbp;i++) {
        if (mQualityCounts[i].count() > 100) {
            count++;
            total += mQualityCounts[i].percentile(percentile);
        }
    }

    if (count > 0) {
        return total/count;
    }
    return 0;
}

void PerBaseQualityAnalysis::computePercentages()
{
    QList<BaseGroup> groups =BaseGroup::makeBaseGroups(mQualityCounts.length());

    means.fill(0,groups.length());
    medians.fill(0,groups.length());
    lowest.fill(0,groups.length());
    highest.fill(0,groups.length());
    lowerQuartile.fill(0,groups.length());
    upperQuartile.fill(0,groups.length());
    xLabels.fill(QString(), groups.length());

    for (int i=0;i<groups.length();i++) {
        int minBase = groups[i].lowerCount();
        int maxBase = groups[i].upperCount();

        lowest[i]  = percentile(minBase, maxBase, 10);
        highest[i] = percentile(minBase, maxBase, 90);
        means[i]   = mean(minBase,maxBase);
        medians[i] = percentile(minBase, maxBase, 50);
        lowerQuartile[i] = percentile(minBase, maxBase, 25);
        upperQuartile[i] = percentile(minBase, maxBase, 75);
        xLabels[i] = groups[i].toString();


    }

    qDebug()<<means;
}



//===========================================================
//
//
//
//===========================================================


QualityCount::QualityCount()
{

    mTotalCounts = 0;


}

void QualityCount::addValue(char c)
{
    mTotalCounts++;
    mCounts[c] = mCounts.value(c,0) + 1;

}

qreal QualityCount::mean()const
{
    quint64 total = 0;
    quint64 count = 0;

    for (char c : mCounts.keys())
    {
        count += mCounts[c];
        total += mCounts[c] * c;
    }

    return qreal(total) / count;

}

char QualityCount::min()const
{
    char minChar = mCounts.keys().first();
    for (char c : mCounts.keys())
        minChar = qMin(minChar, c);


    return minChar;

}

char QualityCount::max()const
{
    char maxChar = mCounts.keys().first();
    for (char c : mCounts.keys())
        maxChar = qMax(maxChar, c);


    return maxChar;
}

qreal QualityCount::percentile(int percentile)const
{
    QList<char> keys = mCounts.keys();
    qSort(keys.begin(), keys.end());

    int total = 0;
    for (char c : keys)
        total += mCounts[c];

    total *= percentile;
    total /= 100;

    int count = 0;
    for (char c : keys)
    {
        count += mCounts[c];
        if (count >= total)
            return c;
    }


    return -1;

}

int QualityCount::count()const
{
    return mTotalCounts;
}

