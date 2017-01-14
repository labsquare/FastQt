/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of fastQT.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "perbasequalityanalysis.h"
#include "sequence.h"

QualityCount::QualityCount()
{



}

inline void QualityCount::addValue(char c)
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

//===========================================================
//
//
//
//===========================================================

PerBaseQualityAnalysis::PerBaseQualityAnalysis()
{
    setName("PerBase analysis");
}

void PerBaseQualityAnalysis::processSequence(const Sequence &sequence)
{



    if ( mQualityCounts.size() < sequence.quality().size())
        mQualityCounts.resize(sequence.size());


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
    QLineSeries  *lineseries = new QLineSeries ();

    for (int i=0; i<means.size(); ++i)
    {
        QBoxSet *box = new QBoxSet(xLabels[i]);
        box->setValue(QBoxSet::LowerExtreme, lowest[i]);
        box->setValue(QBoxSet::UpperExtreme, highest[i]);
        box->setValue(QBoxSet::Median, medians[i]);
        box->setValue(QBoxSet::LowerQuartile,lowerQuartile[i]);
        box->setValue(QBoxSet::UpperQuartile, upperQuartile[i]);
        lineseries->append(QPoint(i,means[i]));


        qualSerie->append(box);
    }


    QChart * chart = new QChart();
    chart->addSeries(qualSerie);
    chart->addSeries(lineseries);
    chart->createDefaultAxes();
    chart->setTitle("Quality per base");
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->setBackgroundRoundness(5);

    // customize look
    QPen pen;
    QBrush brush("#249de4");
    pen.setWidth(1);
    qualSerie->setPen(pen);
    qualSerie->setBrush(brush);
    qualSerie->setName("Quality per base");

    pen.setColor("#f5a800");
    pen.setWidth(3);
    lineseries->setPen(pen);
    lineseries->setName("Means qualities");


    // Customize grid lines and shades
    QAbstractAxis * axisY = chart->axisY(qualSerie);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    brush.setColor(QColor(0,0,0,10));
    axisY->setShadesBrush(brush);
    axisY->setShadesVisible(true);

    // Customize xLabel orientation
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
