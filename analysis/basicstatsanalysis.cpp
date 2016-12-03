#include "basicstatsanalysis.h"
#include <QDebug>
BasicStatsAnalysis::BasicStatsAnalysis()
    :Analysis()
{
    setName("Basic Stat");
}
// ==============================================================
void BasicStatsAnalysis::reset()
{
    mEncoding.clear();
    mReadCount = 0;
    mMinLength = 0;
    mMaxLength = 0;
}
// ==============================================================

void BasicStatsAnalysis::processSequence(const Sequence &sequence)
{


    mReadCount++;

    if (mReadCount == 1)
        mMinLength = sequence.size();


    mMinLength = qMin(mMinLength, sequence.size());
    mMaxLength = qMax(mMaxLength, sequence.size());


}
// ==============================================================

QWidget *BasicStatsAnalysis::createResultWidget()
{

    QTableView * view = new QTableView;
    KeyValueModel * model = new KeyValueModel(view);
    view->setModel(model);

    QString length = mMinLength == mMaxLength ? QString("%1").arg(mMaxLength) :  QString("%1-%2").arg(mMinLength).arg(mMaxLength);


    model->addValue(QObject::tr("Total Sequences"), mReadCount);
    model->addValue(QObject::tr("Sequence length"), length);

    view->horizontalHeader()->hide();
    view->verticalHeader()->hide();

    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);


    view->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);


    return view;


}
