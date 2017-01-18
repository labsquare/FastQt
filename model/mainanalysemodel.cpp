#include "mainanalysemodel.h"

MainAnalyseModel::MainAnalyseModel(QObject * parent)
    :QAbstractListModel(parent)
{
    mSignalMapper = new QSignalMapper(this);

    connect(mSignalMapper,SIGNAL(mapped(int)),this,SLOT(updated(int)));
}

int MainAnalyseModel::rowCount(const QModelIndex &parent) const
{
    return mRunners.size();
}

int MainAnalyseModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MainAnalyseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
    {
        if (index.column() == 0){
            QFileInfo info(mRunners.at(index.row())->filename());
            return info.fileName();

        }

        if (index.column() == 1)
            return mRunners.at(index.row())->lastMessage();


        if (index.column() == 2)
            return mRunners.at(index.row())->progression();
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

    connect(runner,SIGNAL(updated(QString)), mSignalMapper,SLOT(map()));
    int runnerRow = mRunners.size(); // this is the row number
    mSignalMapper->setMapping(runner,runnerRow);
    mRunners.append(runner);
    endInsertRows();

    emit layoutChanged();

    runner->start();



}

void MainAnalyseModel::updated(int row)
{

    QModelIndex left  = index(row,1);
    QModelIndex right = index(row,columnCount());

    emit dataChanged(left, right);


}
