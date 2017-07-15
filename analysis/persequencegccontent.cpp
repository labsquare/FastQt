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
    if(mXMax < (quint64)(sequence.size()))
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
    for(quint64 i = 0; i != mXMax; i++)
        reacheable << qRound((i/75.0) * 100);

    for(quint64 i = 0; i != 101; i++)
        not_reacheable << i;

    not_reacheable -= reacheable;

    /* Compute theorical distribution */
    qreal gcMean = mean_ponderate(mGCCounts);
    qreal gcStddev = stddev(mGCCounts, gcMean);

    QChartView * view = new QChartView;
    view->setRubberBand(QChartView::HorizontalRubberBand);
    view->setRenderHint(QPainter::Antialiasing);

    QLineSeries * normalseries = new QLineSeries();
    QLineSeries * lineseries = new QLineSeries();

    qreal yMax = 0;
    for(int i = 0; i != mGCCounts.size(); i++)
    {
        if(!not_reacheable.contains(i))
        {
            lineseries->append(QPoint(i, mGCCounts[i]));
            normalseries->append(QPoint(i, normal_distribution(gcMean, gcStddev, i)*mNbSeq));

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
    axisX->setTitleText(tr("Percent of GC (%)"));

    chart->setAxisX(axisX);

    QValueAxis * axisY= new QValueAxis;
    axisY->setTickCount(10);
    axisY->setRange(0, yMax);
    axisY->setLabelFormat("%d");
    axisY->setTitleText(tr("Read count(s)"));

    chart->setAxisY(axisY);

    view->setChart(chart);

    // add Actions
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
