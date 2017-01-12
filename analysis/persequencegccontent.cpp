#include "persequencegccontent.h"

PerSequenceGCContent::PerSequenceGCContent()
{
    setName("Sequence GC %");
    setDescription("Per sequence gc %");

    /* Series is in 0 and 100 -> 101 values*/
    mGCCounts.resize(101);
}

void PerSequenceGCContent::processSequence(const Sequence& sequence)
{
    mGCCounts[qRound(sequence.gc_percent())]++;
}

void PerSequenceGCContent::reset()
{
    mGCCounts.clear();
    mGCCounts.resize(101);
}

QWidget* PerSequenceGCContent::createResultWidget()
{
    QChartView * view = new QChartView;

    QLineSeries * lineseries = new QLineSeries();

    for(int i = 0; i != mGCCounts.size(); i++)
    {
        lineseries->append(QPoint(i, mGCCounts[i]));
    }

    QChart * chart = new QChart();
    chart->addSeries(lineseries);
    chart->setTitle("Sequence GC %");
    chart->setAnimationOptions(QChart::NoAnimation);

    QValueAxis * axisX = new QValueAxis;
    axisX->setTickCount(10);
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%i");
    chart->setAxisX(axisX);

    QValueAxis * axisY= new QValueAxis;
    axisY->setTickCount(10);
    axisY->setRange(0, 100);
    axisY->setLabelFormat("%.2f%");

    chart->setAxisY(axisY);


    view->setChart(chart);
    return view;
}
