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
#include "perbasecontentanalysis.h"
#include "sequence.h"

PerBaseContentAnalysis::PerBaseContentAnalysis()
    :Analysis()
{

    setName("Per Base content");
    setDescription("Per base content");
    for (int i = 0; i < 256; ++i) {
      counts[i] = &mXCounts;
    }
    counts['G'] = &mGCounts;
    counts['A'] = &mACounts;
    counts['T'] = &mTCounts;
    counts['C'] = &mCCounts;
}

void PerBaseContentAnalysis::processSequence(const Sequence &sequence)
{


    if (mGCounts.size() < sequence.size())
    {
        mGCounts.resize(sequence.size());
        mACounts.resize(sequence.size());
        mTCounts.resize(sequence.size());
        mCCounts.resize(sequence.size());
        mXCounts.resize(sequence.size());
    }


    for (int i=0; i<sequence.size(); ++i)
      ++(*counts[static_cast<int>(sequence.sequence().at(i))])[i];
}

void PerBaseContentAnalysis::reset()
{
    mGCounts.clear();
    mACounts.clear();
    mTCounts.clear();
    mCCounts.clear();

    gPercent.clear();
    aPercent.clear();
    tPercent.clear();
    cPercent.clear();
}

QWidget *PerBaseContentAnalysis::createResultWidget()
{

    computePercentages();

    QLineSeries  * ASerie = new QLineSeries ();
    QLineSeries  * GSerie = new QLineSeries ();
    QLineSeries  * CSerie = new QLineSeries ();
    QLineSeries  * TSerie = new QLineSeries ();


    for (int i=0; i<gPercent.size(); ++i)
    {
        ASerie->append(i, aPercent[i]);
        GSerie->append(i, gPercent[i]);
        CSerie->append(i, cPercent[i]);
        TSerie->append(i, tPercent[i]);
    }


    QChart * chart = new QChart();
    chart->addSeries(ASerie);
    chart->addSeries(GSerie);
    chart->addSeries(CSerie);
    chart->addSeries(TSerie);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, mGCounts.size());
    axisX->setLabelFormat("%.0f");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 100.00);
    axisY->setLabelFormat("%.2f%");

    chart->setAxisX(axisX);
    chart->setAxisY(axisY);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor("#71e096"));
    ASerie->setPen(pen);

    pen.setColor(QColor("#5AD0E5"));
    CSerie->setPen(pen);

    pen.setColor(QColor("#ED6D79"));
    TSerie->setPen(pen);


    pen.setColor(QColor("darkgray"));
    GSerie->setPen(pen);



    chart->setTitle("Per Base content");
    chart->setAnimationOptions(QChart::NoAnimation);



    QChartView * view = new QChartView;
    view->setChart(chart);

    return view;
}

void PerBaseContentAnalysis::computePercentages()
{


    QVector<BaseGroup> groups = BaseGroup::makeBaseGroups(mGCounts.size());
    mXCategories.resize(groups.length());

    gPercent.resize(groups.length());
    aPercent.resize(groups.length());
    tPercent.resize(groups.length());
    cPercent.resize(groups.length());


    quint64 total;
    quint64 gCount;
    quint64 aCount;
    quint64 tCount;
    quint64 cCount;


    for (int i=0;i<groups.length();i++) {

        mXCategories[i] = groups[i].toString();

        gCount = 0;
        aCount = 0;
        tCount = 0;
        cCount = 0;
        total  = 0;

        for (int bp=groups[i].lowerCount()-1;bp<groups[i].upperCount();bp++) {

            total += mGCounts[bp];
            total += mCCounts[bp];
            total += mACounts[bp];
            total += mTCounts[bp];

            aCount += mACounts[bp];
            tCount += mTCounts[bp];
            cCount += mCCounts[bp];
            gCount += mGCounts[bp];
        }



        gPercent[i] = (gCount/(double)total)*100;
        aPercent[i] = (aCount/(double)total)*100;
        tPercent[i] = (tCount/(double)total)*100;
        cPercent[i] = (cCount/(double)total)*100;

    }
}
