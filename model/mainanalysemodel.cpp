#include "mainanalysemodel.h"

MainAnalyseModel::MainAnalyseModel(QObject * parent)
    :QAbstractListModel(parent)
{
    mTimer = new QTimer(this);
//   mSignalMapper = new QSignalMapper(this);
//    connect(mSignalMapper,SIGNAL(mapped(int)),this,SLOT(updated(int)));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(timeUpdated()));

    mTimer->setInterval(1000);
}

int MainAnalyseModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mRunners.size();
}

int MainAnalyseModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

QVariant MainAnalyseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
    {
        if (index.column() == NameColumn){
            QFileInfo info(mRunners.at(index.row())->filename());
            return info.fileName();
        }

        if (index.column() == SizeColumn)
            return mRunners.at(index.row())->humanFileSize();


        if (index.column() == ProgressColumn)
            return mRunners.at(index.row())->progression();

        if (index.column() == ReadsColumn)
            return mRunners.at(index.row())->sequenceCount();


        if (index.column() == TimeColumn){
            QTime time;
            time.setHMS(0,0,0);
            time = time.addMSecs(mRunners.at(index.row())->duration());
            return time.toString();
        }
    }

    if (role == Qt::DecorationRole)
    {
        if (index.column() == 0)
        {

            return QFontIcon::icon(0xf017, qApp->palette("QWidget").highlight().color());


        }
    }


    return QVariant();

}

QVariant MainAnalyseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case NameColumn : return tr("Filename");break;
            case SizeColumn: return tr("File size"); break;
            case ProgressColumn : return tr("Progress"); break;
            case ReadsColumn : return tr("Reads");break;
            case TimeColumn: return tr("Time"); break;
            }
        }
    }
    return QVariant();
}

void MainAnalyseModel::addFile(const QString &filename)
{
    beginInsertRows(QModelIndex(), 0,0);

    AnalysisRunner * runner = new AnalysisRunner(filename);
    runner->addAnalysis(new BasicStatsAnalysis);
    runner->addAnalysis(new PerBaseQualityAnalysis);
    runner->addAnalysis(new PerSequenceQualityAnalysis);
    runner->addAnalysis(new PerBaseContentAnalysis);
    runner->addAnalysis(new OverRepresentedSeqsAnalysis);
    runner->addAnalysis(new PerBaseNContentAnalysis);
    runner->addAnalysis(new PerSequenceGCContent);
    runner->addAnalysis(new LengthDistributionAnalysis);

   // connect(runner,SIGNAL(updated(QString)), mSignalMapper,SLOT(map()));
    int runnerRow = mRunners.size(); // this is the row number
   // mSignalMapper->setMapping(runner,runnerRow);

    mRunners.append(runner);
    endInsertRows();

    emit layoutChanged();

    runner->start();

    if (!mTimer->isActive())
        mTimer->start();

}

void MainAnalyseModel::updated(int row)
{

    QModelIndex left  = index(row,1);
    QModelIndex right = index(row,columnCount());

    //emit dataChanged(left,right);


}

void MainAnalyseModel::timeUpdated()
{
    if (rowCount() == 0)
        return;

    qDebug()<<"update";

    QModelIndex top    = index(0, 1);
    QModelIndex bottom = index(rowCount(),columnCount());

    emit dataChanged(top, bottom);

}
