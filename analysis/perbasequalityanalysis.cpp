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
    QSplineSeries  *lineseries = new QSplineSeries ();


    for (int i=0; i<means.size(); ++i)
    {
        QBoxSet *box = new QBoxSet(xLabels[i]);
        box->setValue(QBoxSet::LowerExtreme, lowest[i]);
        box->setValue(QBoxSet::UpperExtreme, highest[i]);
        box->setValue(QBoxSet::Median, medians[i]);
        box->setValue(QBoxSet::LowerQuartile,lowerQuartile[i]);
        box->setValue(QBoxSet::UpperQuartile, upperQuartile[i]);


        lineseries->append(QPoint(i,means[i]));

        QPen pen = box->pen();
        pen.setWidth(1);
        pen.setStyle(Qt::SolidLine);
        box->setPen(pen);


        qualSerie->append(box);

    }


    QPen pen(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);

    lineseries->setPen(pen);
    QChart * chart = new QChart();
    chart->addSeries(qualSerie);
    chart->addSeries(lineseries);



    chart->setTitle("Quality per base");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//    chart->setTheme(QChart::ChartThemeQt);











//    QLinearGradient plotAreaGradient;
//    plotAreaGradient.setStart(QPointF(0, 0));
//    plotAreaGradient.setStart(QPointF(0, 0.5));

//    plotAreaGradient.setFinalStop(QPointF(0, 1));

//    plotAreaGradient.setColorAt(0.0, QColor("red"));
//    plotAreaGradient.setColorAt(0.5, QColor("orange"));

//    plotAreaGradient.setColorAt(1.0, QColor("green"));

//    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
//    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
//    chart->setPlotAreaBackgroundVisible(true);

    chart->createDefaultAxes();


    QFont labelsFont;
    labelsFont.setPixelSize(5);

    chart->axisX(qualSerie)->setLabelsAngle(90);
    chart->axisX(lineseries)->hide();



    QChartView * view = new QChartView;
    view->setChart(chart);



    return view;

}

qreal PerBaseQualityAnalysis::mean(int minbp, int maxbp, int offset)
{
    int count    = 0;
    double total = 0;

    for (int i=minbp-1;i<maxbp;i++) {
        if (mQualityCounts[i].count() > 0) {
            count++;
            total += mQualityCounts[i].mean(offset);
        }
    }

    if (count > 0) {
        return total/count;
    }
    return 0;


}

qreal PerBaseQualityAnalysis::percentile(int minbp, int maxbp,int offset, int percentile)
{
    int count = 0;
    double total = 0;

    for (int i=minbp-1;i<maxbp;i++) {
        if (mQualityCounts[i].count() > 100) {
            count++;
            total += mQualityCounts[i].percentile(offset,percentile);
        }
    }

    if (count > 0) {
        return total/count;
    }
    return 0;
}

void PerBaseQualityAnalysis::computePercentages()
{

    auto range = computeOffsets();
    mEncodingScheme = PhredEncoding::fastqEncodingOffset(range.first);
    mLow  = 0;
    mHigh = range.second - mEncodingScheme.offset();
    if (mHigh < 35)
        mHigh = 35;




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

        lowest[i]  = percentile(minBase, maxBase, mEncodingScheme.offset(), 10);
        highest[i] = percentile(minBase, maxBase, mEncodingScheme.offset(), 90);
        means[i]   = mean(minBase,maxBase, mEncodingScheme.offset());
        medians[i] = percentile(minBase, maxBase, mEncodingScheme.offset(),50);
        lowerQuartile[i] = percentile(minBase, maxBase,mEncodingScheme.offset(), 25);
        upperQuartile[i] = percentile(minBase, maxBase,mEncodingScheme.offset(), 75);
        xLabels[i] = groups[i].toString();


    }

}

QPair<char, char> PerBaseQualityAnalysis::computeOffsets()
{
    // Works out from the set of chars what is the most
    // likely encoding scale for this file.

    char minChar = 0;
    char maxChar = 0;
    bool first = true;
    for (QualityCount i : mQualityCounts)
    {
        if (first)
        {
            minChar = i.min();
            maxChar = i.max();
            first   = false;
        }
        else
        {
            minChar = qMin(i.min(), minChar);
            maxChar = qMax(i.max(), maxChar);

        }
    }
    return qMakePair(minChar, maxChar);

}

//===========================================================
//
//
//
//===========================================================

QualityCount::QualityCount()
{



}

void QualityCount::addValue(char c)
{
    mTotalCounts++;
    mCounts[int(c)]++;
}


char QualityCount::min()const
{
    for (int i=0; i<QUALITY_COUNT_SIZE; ++i)
    {
        if (mCounts[i] != 0)
            return char(i);
    }

    return char(1000);
}

char QualityCount::max()const
{

    for (int i=QUALITY_COUNT_SIZE-1; i>=0; --i)
    {
        if (mCounts[i] != 0)
            return char(i);

    }
    return char(1000);
}

qreal QualityCount::mean(int offset)const
{
    quint64 total = 0;
    quint64 count = 0;

    for (int i=offset; i<QUALITY_COUNT_SIZE; ++i)
    {
        count += mCounts[i];
        total += mCounts[i] * (i-offset);

    }
    return qreal(total) / count;
}
qreal QualityCount::percentile(int offset, int percentile)const
{
    int total = mTotalCounts;

    total *= percentile;
    total /= 100;

    int count = 0;
    for (int i=offset;i<QUALITY_COUNT_SIZE;i++) {
        count += mCounts[i];
        if (count >=total) {
            return((char)(i-offset));
        }
    }

    return -1;

}

int QualityCount::count()const
{
    return mTotalCounts;
}

