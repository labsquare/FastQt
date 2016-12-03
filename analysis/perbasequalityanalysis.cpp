#include "perbasequalityanalysis.h"

PerBaseQualityAnalysis::PerBaseQualityAnalysis()
{
    setName("PerBase analysis");
}

void PerBaseQualityAnalysis::processSequence(const Sequence &sequence)
{



    if ( mQualityCounts.length() < sequence.quality().length())
    {
        mQualityCounts.clear();

        for (int i= mQualityCounts.count(); i<sequence.quality().length(); ++i)
            mQualityCounts.append(QualityCount());

    }


    for (int i=0; i< sequence.quality().length(); ++i)
        mQualityCounts[i].addValue(sequence.quality().at(i));








}

void PerBaseQualityAnalysis::reset()
{
    mQualityCounts.clear();
}

QWidget *PerBaseQualityAnalysis::createResultWidget()
{


    qSort(sortedList.begin(), sortedList.end());

    int count = sortedList.count();

    QBoxSet *box = new QBoxSet("graph");
    box->setValue(QBoxSet::LowerExtreme, sortedList.first());
    box->setValue(QBoxSet::UpperExtreme, sortedList.last());
    box->setValue(QBoxSet::Median, findMedian(0, count));
    box->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
    box->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + (count % 2), count));


    QBoxPlotSeries *acmeSeries = new QBoxPlotSeries();
    acmeSeries->append(box);

    QChart * chart = new QChart();
    chart->addSeries(acmeSeries);

    QChartView * view = new QChartView;
    view->setChart(chart);

    return view;

}

qreal PerBaseQualityAnalysis::findMedian(int begin, int end)
{

    int count = end - begin;
    if (count % 2) {
        return sortedList.at(count / 2 + begin);
    } else {
        qreal right = sortedList.at(count / 2 + begin);
        qreal left = sortedList.at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
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
    mCounts[c] = mCounts.value(c,0) + 1;

}

qreal QualityCount::mean()
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

char QualityCount::min()
{
    char minChar = mCounts.keys().first();
    for (char c : mCounts.keys())
        minChar = qMin(minChar, c);


    return minChar;

}

char QualityCount::max()
{
    char maxChar = mCounts.keys().first();
    for (char c : mCounts.keys())
        maxChar = qMax(maxChar, c);


    return maxChar;
}

qreal QualityCount::percentile(int percentile)
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

