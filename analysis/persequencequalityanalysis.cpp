#include "persequencequalityanalysis.h"

PerSequenceQualityAnalysis::PerSequenceQualityAnalysis()
    :Analysis()
{

    setName("Sequence quality");
    setTooltip("Per sequence quality scores");

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

 QSplineSeries  *lineseries = new QSplineSeries ();

 QList<int> keys       = mAverageScoreCounts.keys();
 QList<quint64> values = mAverageScoreCounts.values();

 qSort(keys);
 qSort(values);

 for (int key : keys )
 {
     lineseries->append(QPoint(key, mAverageScoreCounts[key]));
 }


    QChart * chart = new QChart();
    chart->addSeries(lineseries);
    chart->setTitle("Quality per base");
    chart->setAnimationOptions(QChart::NoAnimation);

    QValueAxis * axisX= new QValueAxis;
    axisX->setTickCount(10);
    axisX->setRange(keys.first(), keys.last());
    axisX->setLabelFormat("%i");
    chart->setAxisX(axisX);

    QValueAxis * axisY= new QValueAxis;
    axisY->setTickCount(10);
    axisY->setRange(values.first(), values.last());
    axisY->setLabelFormat("%i");

    chart->setAxisY(axisY);


    QChartView * view = new QChartView;
    view->setChart(chart);

    return view;
}
