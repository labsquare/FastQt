#include "seqqualityanalysewidget.h"


#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
SeqQualityAnalyseWidget::SeqQualityAnalyseWidget(FastqProcess * reader, QWidget * parent):
    AbstractAnalyseWidget(reader,parent)
{

    setWindowTitle("Quality");
    setWindowIcon(QIcon::fromTheme("edit-undo"));


}

void SeqQualityAnalyseWidget::fill()
{

    QBoxPlotSeries *testSeries = new QBoxPlotSeries();
    testSeries->setBoxOutlineVisible(false);
    testSeries->setName("Acme Ltd");

    int index = 0;
    for (QualitySet it : reader()->results().qualities)
    {


        QBoxSet * set = new QBoxSet;

        *set<<it.min<<it.first_quartile<<it.median<<it.last_quartile<<it.max;

        testSeries->append(set);
    }


    QChart * chart = new QChart();
    chart->addSeries(testSeries);
    ////    chart->axisY()->setMin(0);
    ////    chart->axisY()->setMax(34.0);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);


}
