/*
Copyright Copyright 2017 Pierre Marijon

    This file is part of CuteVCF.

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
#include "perbasencontentanalysis.h"
#include "sequence/sequence.hxx"

PerBaseNContentAnalysis::PerBaseNContentAnalysis()
    :Analysis()
{

    setName("Per Base N content");
    setDescription("Per base N content");
    for (int i = 0; i < 256; ++i) {
      counts[i] = &mXCounts;
    }

    counts['N'] = &mNCounts;
}

void PerBaseNContentAnalysis::processSequence(const Sequence &sequence)
{


    if (mXCounts.size() < sequence.size())
    {
        mNCounts.resize(sequence.size());
        mXCounts.resize(sequence.size());
    }


    for (int i=0; i<sequence.size(); ++i)
      ++(*counts[static_cast<int>(sequence.sequence().at(i))])[i];
}

void PerBaseNContentAnalysis::reset()
{
    mNCounts.clear();

    nPercent.clear();
}

QWidget *PerBaseNContentAnalysis::createResultWidget()
{

    computePercentages();

    QLineSeries * NSerie = new QLineSeries ();

    for (int i=0; i<nPercent.size(); ++i)
    {
        NSerie->append(i, nPercent[i]);
    }


    QChart * chart = new QChart();
    chart->addSeries(NSerie);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, mNCounts.size());
    axisX->setLabelFormat("%.0f");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 100.00);
    axisY->setLabelFormat("%.2f%");

    chart->setAxisX(axisX);
    chart->setAxisY(axisY);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor("#71e096"));
    NSerie->setPen(pen);

    chart->setTitle("Per Base N content");
    chart->setAnimationOptions(QChart::NoAnimation);


    QChartView * view = new QChartView;
    view->setChart(chart);

    return view;
}

void PerBaseNContentAnalysis::computePercentages()
{


    QVector<BaseGroup> groups = BaseGroup::makeBaseGroups(mNCounts.size());
    mXCategories.resize(groups.length());

    nPercent.resize(groups.length());

    quint64 total;
    quint64 nCount;

    for (int i=0;i<groups.length();i++) {

        mXCategories[i] = groups[i].toString();

        nCount = 0;
        total  = 0;

        for (int bp=groups[i].lowerCount()-1;bp<groups[i].upperCount();bp++) {

            total += mNCounts[bp];
            total += mXCounts[bp];

            nCount += mNCounts[bp];
        }


        nPercent[i] = (nCount/(double)total)*100;
    }
}
