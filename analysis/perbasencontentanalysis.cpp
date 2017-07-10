/*
Copyright 2016-17 Pierre Marijon

    This file is part of FastQt.

    FastQt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastQt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastQt.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "perbasencontentanalysis.h"
#include "sequence.h"

PerBaseNContentAnalysis::PerBaseNContentAnalysis(QObject * parent)
    :Analysis(parent)
{

    setName(tr("Per Base N content"));
    setDescription(tr("Per base N content"));
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


    QLineSeries * NSerie = new QLineSeries ();

    qreal xMul = mNCounts.size()/nPercent.size();
    for (int i=0; i<nPercent.size(); ++i)
    {
        NSerie->append(i * xMul, nPercent[i]);
    }


    QChart * chart = new QChart();
    chart->addSeries(NSerie);

    /* Create fake series for set the chart dimension */
    QLineSeries * fakeSerie = new QLineSeries();
    fakeSerie->append(0, 0);
    fakeSerie->append(nPercent.size(), 100);
    fakeSerie->setVisible(false);
    chart->addSeries(fakeSerie);

    chart->createDefaultAxes();

    /* Set label of axis */
    dynamic_cast<QValueAxis*>(chart->axisX())->setLabelFormat("%d");
    dynamic_cast<QValueAxis*>(chart->axisY())->setLabelFormat("%.2f %");

    chart->axisX()->setTitleText(tr("Position in read (bp)"));
    chart->axisY()->setTitleText(tr("N percent (%)"));


    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor("#71e096"));
    NSerie->setPen(pen);

    chart->setTitle(tr("Per Base N content"));
    chart->setAnimationOptions(QChart::NoAnimation);


    QChartView * view = new QChartView;
    view->setRenderHint(QPainter::Antialiasing);

    view->setChart(chart);
    // add Actions
    view->setRubberBand(QChartView::HorizontalRubberBand);
    QAction * zoomReset = new QAction(QFontIcon::icon(0xf002), tr("Zoom reset"), view);
    QAction * zoomIn    = new QAction(QFontIcon::icon(0xf00e), tr("Zoom in"), view);
    QAction * zoomOut   = new QAction(QFontIcon::icon(0xf010), tr("Zoom out"), view);

    connect(zoomReset, &QAction::triggered, [chart](){chart->zoomReset();});
    connect(zoomIn, &QAction::triggered, [chart](){chart->zoomIn();});
    connect(zoomOut, &QAction::triggered, [chart](){chart->zoomOut();});

    view->addAction(zoomReset);
    view->addAction(zoomIn);
    view->addAction(zoomOut);
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

void PerBaseNContentAnalysis::after()
{
    computePercentages();
}
