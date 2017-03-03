#include "mainanalysemodel.h"
#include "perbasequalityanalysis.h"

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
    return 6;
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

        if (index.column() == StatusColumn)
        {
            switch (mRunners.at(index.row())->status())
            {
            case AnalysisRunner::Waiting : return tr("Waiting"); break;
            case AnalysisRunner::Canceled : return tr("Canceled"); break;
            case AnalysisRunner::Running : return tr("Running"); break;
            case AnalysisRunner::Finished : return tr("Finished"); break;
            }

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
        if (index.column() == ReadsColumn && mRunners.at(index.row())->status() == AnalysisRunner::Finished)
            return mRunners.at(index.row())->analysis(PerBaseQualityAnalysis::staticMetaObject.className())->statusIcon();

        if (index.column() == StatusColumn)
        {
            switch (mRunners.at(index.row())->status())
            {
            case AnalysisRunner::Waiting : return QFontIcon::icon(0xf017, Qt::darkGray); break;
            case AnalysisRunner::Canceled: return QFontIcon::icon(0xf071,Qt::darkRed); break;
            case AnalysisRunner::Running : return QFontIcon::icon(0xf085,Qt::darkGray); break;
            case AnalysisRunner::Finished: return QFontIcon::icon(0xf00c,Qt::darkGreen); break;
            }
        }

        if (index.column() == NameColumn)
        {
            QFileInfo info(mRunners.at(index.row())->filename());

            if (info.suffix().toLower() =="fastq")
                return QFontIcon::icon(0xf016);

            else
                return QFontIcon::icon(0xf1c6);
        }
    }

    if (role == Qt::TextColorRole)
    {

        if (mRunners.at(index.row())->status() == AnalysisRunner::Waiting)
            return QColor(Qt::lightGray);

        if (index.column() == StatusColumn)
        {
            switch (mRunners.at(index.row())->status())
            {
            case AnalysisRunner::Waiting : return QColor(Qt::lightGray); break;
            case AnalysisRunner::Canceled: return QColor(Qt::darkRed); break;
            case AnalysisRunner::Finished: return QColor(Qt::darkGreen); break;
            }
        }

        return qApp->palette("QWidget").text().color();

    }

    if (role == Qt::ToolTipRole)
    {
        if (index.column() == NameColumn)
        {
            return mRunners.at(index.row())->filename();
        }

        if (index.column() == ReadsColumn)
        {
            return mRunners.at(index.row())->analysis(PerBaseQualityAnalysis::staticMetaObject.className())->description();

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
            case StatusColumn: return tr("Status");break;
            case SizeColumn: return tr("File size"); break;
            case ProgressColumn : return tr("Progress"); break;
            case ReadsColumn : return tr("Reads");break;
            case TimeColumn: return tr("Time"); break;
            }
        }
    }
    return QVariant();
}



void MainAnalyseModel::remove(const QList<int> &index)
{
    QList<int> sorted = index;
    qSort(sorted.begin(),sorted.end(), qGreater<int>());

    beginResetModel();
    for (int i : sorted)
    {
        AnalysisRunner * runner = mRunners.takeAt(i);
        runner->setAutoDelete(true);
    }
    endResetModel();
}


void MainAnalyseModel::addFile(const QString &filename)
{
    beginInsertRows(QModelIndex(), 0,0);

    AnalysisRunner * runner = AnalysisRunner::createAnalysisRunner();
    runner->setFilename(filename);
    mRunners.append(runner);
    endInsertRows();

    emit layoutChanged();

    QThreadPool::globalInstance()->start(runner);

    if (!mTimer->isActive())
        mTimer->start();

}


AnalysisRunner *MainAnalyseModel::runner(const QModelIndex &index)
{
    if (!index.isValid())
        return Q_NULLPTR;

    return mRunners.at(index.row());
}



void MainAnalyseModel::timeUpdated()
{
    if (rowCount() == 0)
        return;


    QModelIndex top    = index(0, 1);
    QModelIndex bottom = index(rowCount(),columnCount());

    emit dataChanged(top, bottom);

}
