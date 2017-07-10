/*
Copyright 2016-17 Sacha Schutz

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
#include "persequencequalityanalysis.h"
#include "sequence.h"

PerSequenceQualityAnalysis::PerSequenceQualityAnalysis(QObject * parent)
    :Analysis(parent)
{

    setName(tr("Sequence quality"));
    setDescription(tr("Per sequence quality scores"));

}

void PerSequenceQualityAnalysis::processSequence(const Sequence &sequence)
{

    int averageQuality = 0;
    for (char bytes : sequence.quality())
    {
        averageQuality += int(bytes);
    }

    if (sequence.size() > 0)
        averageQuality /= sequence.size();

    averageQuality = int(averageQuality);

    if (mAverageScoreCounts.contains(averageQuality))
        mAverageScoreCounts[averageQuality]++;
    else
        mAverageScoreCounts[averageQuality] = 1;



}

void PerSequenceQualityAnalysis::reset()
{
    mAverageScoreCounts.clear();
}

QWidget *PerSequenceQualityAnalysis::createResultWidget()
{

    QLineSeries  *lineseries = new QLineSeries ();

    QList<int> keys       = mAverageScoreCounts.keys();
    QList<quint64> values = mAverageScoreCounts.values();

    QChartView * view = new QChartView;
    view->setRenderHint(QPainter::Antialiasing);

    // avoid crash
    if (keys.isEmpty() || values.isEmpty())
        return view;

    qSort(keys);
    qSort(values);

    for (int key : keys )
    {
        lineseries->append(QPoint(key, mAverageScoreCounts[key]));
    }


    QChart * chart = new QChart();
    chart->addSeries(lineseries);
    chart->setTitle(tr("Sequence quality"));
    chart->setAnimationOptions(QChart::NoAnimation);

    QValueAxis * axisX= new QValueAxis;
    axisX->setTickCount(10);
    axisX->setRange(keys.first(), keys.last());
    axisX->setLabelFormat("%i");
    axisX->setTitleText(tr("Score quality (phred)"));
    chart->setAxisX(axisX);

    QValueAxis * axisY= new QValueAxis;
    axisY->setTickCount(10);
    axisY->setRange(values.first(), values.last());
    axisY->setLabelFormat("%i");
    axisY->setTitleText(tr("Read count(s)"));


    chart->setAxisY(axisY);

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
    view->setChart(chart);

    return view;
}
