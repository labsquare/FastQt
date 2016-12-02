#include "basicstatsanalysis.h"
#include <QDebug>
BasicStatsAnalysis::BasicStatsAnalysis()
    :Analysis()
{
    mTotal = 0;
    setName("Basic Stat");
}

void BasicStatsAnalysis::processSequence(const Sequence &sequence)
{

    mTotal+=1;

}

QWidget *BasicStatsAnalysis::createResultWidget()
{

    return new QSpinBox();


}
