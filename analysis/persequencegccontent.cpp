#include "persequencegccontent.h"
#include "statistic.h"

PerSequenceGCContent::PerSequenceGCContent()
{
    setName("Sequence GC %");
    setDescription("Per sequence gc %");

    /* Series is in 0 and 100 -> 101 values*/
    mGCCounts.resize(101);
    mNbSeq = 0;
}

void PerSequenceGCContent::processSequence(const Sequence& sequence)
{
    mGCCounts[qRound(sequence.gc_percent())]++;
    mNbSeq++;
}

void PerSequenceGCContent::reset()
{
    mGCCounts.clear();
    mGCCounts.resize(101);
    mNbSeq = 0;
}

QWidget* PerSequenceGCContent::createResultWidget()
{
    /* Compute theorical distribution */
    qreal gcMean = mean_ponderate<QVector, quint64, qreal>(mGCCounts);
    qreal gcStddev = stddev<QVector, quint64, qreal>(mGCCounts, gcMean);

    QChartView * view = new QChartView;

    QLineSeries * normalseries = new QLineSeries();
    QLineSeries * lineseries = new QLineSeries();

    for(int i = 0; i != mGCCounts.size(); i++)
    {
        lineseries->append(QPoint(i, mGCCounts[i]));
        normalseries->append(QPoint(i, normal_distribution<qreal, qreal, qreal>(gcMean, gcStddev, i)*mNbSeq));
    }

    QChart * chart = new QChart();
    chart->addSeries(lineseries);
    chart->addSeries(normalseries);
    chart->setTitle("Sequence GC %");
    chart->setAnimationOptions(QChart::NoAnimation);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor("#71e096"));
    normalseries->setPen(pen);

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
