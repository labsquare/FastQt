#include "persequencegccontent.h"

PerSequenceGCContent::PerSequenceGCContent(QObject * parent)
    :Analysis(parent)
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
    view->setRenderHint(QPainter::Antialiasing);

    QLineSeries * lineseries = new QLineSeries();

    qreal yMax = 0;
    for(int i = 0; i != mGCCounts.size(); i++)
    {
        lineseries->append(QPoint(i, mGCCounts[i]));
        if(mGCCounts[i] > yMax)
            yMax = mGCCounts[i];
    }

    QChart * chart = new QChart();
    chart->addSeries(lineseries);
    chart->setTitle("Sequence GC %");
    chart->setAnimationOptions(QChart::NoAnimation);

    QValueAxis * axisX = new QValueAxis;
    axisX->setTickCount(10);
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%.2f %");
    chart->setAxisX(axisX);

    QValueAxis * axisY= new QValueAxis;
    axisY->setTickCount(10);
    axisY->setRange(0, yMax);
    axisY->setLabelFormat("%d");

    chart->setAxisY(axisY);


    view->setChart(chart);
    return view;
}
