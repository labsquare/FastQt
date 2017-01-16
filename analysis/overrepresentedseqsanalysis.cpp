#include "overrepresentedseqsanalysis.h"
#include "sequence.h"

OverRepresentedSeqsAnalysis::OverRepresentedSeqsAnalysis(QObject * parent)
    :Analysis(parent)
{
    setName("Overrepresented sequences");
    setDescription("Identifies sequences which are overrepresented in the set");
}

void OverRepresentedSeqsAnalysis::processSequence(const Sequence &sequence)
{

    ++mCount;



    // Since we rely on identity to match sequences we can't trust really long
    // sequences, so anything over 75bp gets truncated to 50bp.

    QByteArray seq = sequence.sequence();

    if (seq.length() > 75) {
        seq = seq.left(50);
    }


    if (mSequences.contains(seq))
    {
        mSequences[seq]++;
        // We need to increment the count at unique limit just in case
        // we never hit the unique sequence limit, so we need to know
        // that we'd actually seen all of the sequences.
        if (!mFrozen)
            mCountAtUniqueLimit = mCount;
    }

    else
    {
        if (!mFrozen)
            mSequences[seq] = 1;
        mUniqueSequenceCount++;
        mCountAtUniqueLimit = mCount;
        if (mUniqueSequenceCount == OBSERVATION_CUTOFF)
            mFrozen = true;

    }


}

void OverRepresentedSeqsAnalysis::reset()
{
    mFrozen = 0;
    mSequences.clear();
    mCount = 0;
    mCountAtUniqueLimit = 0;
}

QWidget *OverRepresentedSeqsAnalysis::createResultWidget()
{


    QTableView * view  = new QTableView;
    ResultsModel * model = new ResultsModel(view);

    for (QByteArray s : mSequences.keys())
    {
        double percentage = ((double)mSequences[s] / mCount) * 100;
        model->add(s,mSequences[s], percentage);
    }

    model->sort();
    view->verticalHeader()->hide();
    view->setAlternatingRowColors(true);

    view->setModel(model);

    view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //    view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    //    view->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);



    return view;

}
//============================ OVERREPRESENTEDSEQ Class ===============================

OverRepresentedSeq::OverRepresentedSeq(const QByteArray &seq, quint64 count, double percentage)
    :mSeq(seq), mCount(count), mPercentage(percentage)
{

}

const QByteArray &OverRepresentedSeq::seq() const
{
    return mSeq;
}

quint64 OverRepresentedSeq::count() const
{
    return mCount;
}

double OverRepresentedSeq::percentage() const
{
    return mPercentage;
}

bool OverRepresentedSeq::operator <(const OverRepresentedSeq &other) const
{
    return other.count() < count();

}
//============================ RESULT MODEL ===============================

ResultsModel::ResultsModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

ResultsModel::~ResultsModel()
{
    mSeqs.clear();
}

void ResultsModel::add(const QByteArray &seq, quint64 count, double percentage)
{
    mSeqs.append(OverRepresentedSeq(seq,count,percentage));
}

int ResultsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mSeqs.count();
}

int ResultsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 3 ;
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return mSeqs[index.row()].seq();

        if (index.column() == 1)
            return mSeqs[index.row()].count();

        if (index.column() == 2)
            return QString::number(mSeqs[index.row()].percentage(),'f',2) +" %";

    }

    return QVariant();
}

QVariant ResultsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {

            if (section == 0)
                return tr("Sequence");

            if ( section == 1)
                return tr("Count");

            if (section == 2)
                return tr("Percentage");

        }
    }

    return QVariant();
}

void ResultsModel::sort()
{
    beginResetModel();
    qSort(mSeqs);
    endResetModel();
}

void ResultsModel::clear()
{
    mSeqs.clear();
}


