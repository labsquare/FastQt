#include "basicstatsanalysis.h"
#include "sequence/sequence.hxx"
#include <QDebug>
#include <QLocale>
BasicStatsAnalysis::BasicStatsAnalysis()
    :Analysis()
{
    setName("Basic Stat");
    setTooltip("Basic statistic");
    for (int i = 0; i < 256; ++i) {
      count[i] = &mXCount;
    }
    count['G'] = &mGCount;
    count['A'] = &mACount;
    count['T'] = &mTCount;
    count['C'] = &mCCount;
    count['N'] = &mNCount;
}
// ==============================================================
void BasicStatsAnalysis::reset()
{
    mEncoding.clear();

}
// ==============================================================

void BasicStatsAnalysis::processSequence(const Sequence &sequence)
{


    mReadCount++;

    mMinLength = qMin(mMinLength, sequence.size());
    mMaxLength = qMax(mMaxLength, sequence.size());

    for (char base : sequence.sequence())
    {
      ++(*count[static_cast<int>(base)]);
    }



    for (char byte : sequence.quality())
    {
        if (byte < mLowestChar)
            mLowestChar = byte;
    }
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
    model->addValue(QObject::tr("Encoding"), PhredEncoding::fastqEncodingOffset(mLowestChar).name());

    if (mACount + mCCount + mGCount + mTCount > 0)
    {
         qreal percent =  qreal(mGCount + mCCount) * 100 / (mACount + mCCount + mGCount + mTCount);
         model->addValue(QObject::tr("%GC"), QString::number(percent,'f',2));

    }


    view->horizontalHeader()->hide();
    view->verticalHeader()->hide();

    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);


    view->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);


    return view;


}
