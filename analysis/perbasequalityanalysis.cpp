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
    QVector<BaseGroup> groups =BaseGroup::makeBaseGroups(mQualityCounts.length());

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
    mCounts[int(c)]++;


}

qreal QualityCount::mean()const
{
    quint64 total = 0;
    quint64 count = 0;

    for (int i=33; i<76; ++i)
    {
        count += mCounts[i];
        total += mCounts[i] * i;

    }
    return qreal(total) / count;
}

char QualityCount::min()const
{
    for (int i=33; i<76; ++i)
    {
        if (mCounts[i] != 0)
            return i;
    }

    return char(1000);
}

char QualityCount::max()const
{

    for (int i=75; i>=33; --i)
    {
        if (mCounts[i] != 0)
            return i;

    }
    return char(1000);
}

qreal QualityCount::percentile(int percentile)const
{
    int total = mTotalCounts;

    total *= percentile;
    total /= 100;

    int count = 0;
    for (int i=33;i<76;i++) {
        count += mCounts[i];
        if (count >=total) {
            return((char)(i));
        }
    }

    return -1;

}

int QualityCount::count()const
{
    return mTotalCounts;
}

