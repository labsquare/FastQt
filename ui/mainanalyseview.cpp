#include "mainanalyseview.h"

// =============== DELEGATE ============================================

void MainAnalyseDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() == MainAnalyseModel::ProgressColumn)
    {
        int progress = index.data().toInt();
//        if (progress == 100)
//        {
//            QApplication::style()->drawItemText(painter,option.rect,Qt::AlignCenter,option.palette,true,"Done");
//            return;

//        }


        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect.adjusted(5,5,-5,-5);


        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.progress = progress;
        progressBarOption.text = QString ( "%1%" ).arg ( progress );
        progressBarOption.textVisible = true;
        QApplication::style()->drawControl ( QStyle::CE_ProgressBar, &progressBarOption, painter );

    }

    else
        QStyledItemDelegate::paint ( painter, option, index );

}

// =============== VIEW ============================================

MainAnalyseView::MainAnalyseView(QWidget * parent )
    :QTableView(parent)
{
    mModel    = new MainAnalyseModel;
    mDelegate = new MainAnalyseDelegate;

    setModel(mModel);
    setItemDelegate(mDelegate);

    verticalHeader()->hide();

    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setFocusPolicy(Qt::NoFocus);
    horizontalHeader()->setStretchLastSection(true);
    //horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);

    setColumnWidth(0, 400);

    setIconSize(QSize(22,22));
    setShowGrid(false);

    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showAnalysis(QModelIndex)));


    new QShortcut(QKeySequence::Delete,this, SLOT(removeSelection()));




}

void MainAnalyseView::addFile(const QString &filename)
{
    mModel->addFile(filename);

}

void MainAnalyseView::showAnalysis(const QModelIndex &index)
{

    AnalysisRunner * runner = mModel->runner(index);

    if (runner->status() != AnalysisRunner::Finished)
        return;

    if (mAnalysisWidgets.keys().contains(runner)){
        mAnalysisWidgets[runner]->show();
        qApp->setActiveWindow(mAnalysisWidgets[runner]);

    }

    else
    {
        qDebug()<<"Create";
        MainAnalyseWidget * w = new MainAnalyseWidget();
        w->setRunner(runner);
        mAnalysisWidgets.insert(runner,w);
        w->show();
    }

}


void MainAnalyseView::removeSelection()
{
    QList<int> rows;
    for ( QModelIndex index : selectionModel()->selectedRows())
        rows.append(index.row());

    qDebug()<<rows;

}




