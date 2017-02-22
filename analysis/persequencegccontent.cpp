#include "persequencegccontent.h"
#include "statistic.h"

PerSequenceGCContent::PerSequenceGCContent(QObject * parent)
    :Analysis(parent)
{
    setName(tr("Sequence GC %"));
    setDescription(tr("Per sequence gc %"));

    /* Series is in 0 and 100 -> 101 values*/
    mGCCounts.resize(101);
    mNbSeq = 0;
    mXMax = 0;
}

void PerSequenceGCContent::processSequence(const Sequence& sequence)
{
    mGCCounts[qRound(sequence.gc_percent())]++;
    mNbSeq++;
    if(mXMax < sequence.size())
        mXMax = sequence.size();
}

void PerSequenceGCContent::reset()
{
    mGCCounts.clear();
    mGCCounts.resize(101);
    mNbSeq = 0;
    mXMax = 0;
}

QWidget* PerSequenceGCContent::createResultWidget()
{
    /* Compute gc% not reacheable value */
    QSet<int> not_reacheable;
    QSet<int> reacheable;
    for(int i = 0; i != mXMax; i++)
        reacheable << qRound((i/75.0) * 100);

    for(int i = 0; i != 101; i++)
        not_reacheable << i;

    not_reacheable -= reacheable;

    /* Compute theorical distribution */
    qreal gcMean = mean_ponderate(mGCCounts);
    qreal gcStddev = stddev(mGCCounts, gcMean);

    QChartView * view = new QChartView;
    view->setRenderHint(QPainter::Antialiasing);

    QLineSeries * normalseries = new QLineSeries();
    QLineSeries * lineseries = new QLineSeries();

    qreal yMax = 0;
    for(int i = 0; i != mGCCounts.size(); i++)
    {
        if(!not_reacheable.contains(i))
        {
            lineseries->append(QPoint(i, mGCCounts[i]));
            normalseries->append(QPoint(i, normal_distribution<qreal, qreal, qreal>(gcMean, gcStddev, i)*mNbSeq));

            if(mGCCounts[i] > yMax)
                yMax = mGCCounts[i];
        }
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
