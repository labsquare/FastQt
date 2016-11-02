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

//    int index = 0;
//    for (auto it : reader()->results().qualities)
//    {

//        QBoxSet * set = new QBoxSet;
//        qSort(it.begin(), it.end());


//        qreal min = it.first();
//        qreal max = it.last();

//        int lower = it.size() / 4;
//        int upper = lower * 3;

//        qreal lowerQuart = it.at(lower);
//        qreal upperQuart = it.at(upper);
//        int median ;
//        if (!it.size() % 2)
//            median = it.at((it.size()+1) / 2) ;
//        else
//            median = (it.at(it.size()/2) + it.at((it.size()/2)+1)) / 2;

//        *set<<min<<lowerQuart<<median<<upperQuart<<max;

//        testSeries->append(set);
//    }




//    for (int i=0; i< testSeries->boxSets().first()->count(); ++i)
//    {
//        qDebug()<<i;
//    }

//    QChart * chart = new QChart();
//    chart->addSeries(testSeries);
//    ////    chart->axisY()->setMin(0);
//    ////    chart->axisY()->setMax(34.0);
//    //    //chart->setAnimationOptions(QChart::SeriesAnimations);
//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);

//    QVBoxLayout * mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(chartView);

//    setLayout(mainLayout);


}
