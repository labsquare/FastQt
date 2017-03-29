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

        if( option.state & QStyle::State_Selected )
        {
            painter->fillRect( option.rect, option.palette.highlight() );
        }


        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect.adjusted(5,5,-5,-5);


        progressBarOption.minimum = 0;
        progressBarOption.maximum = progress == -1 ? 0 : 100;
        progressBarOption.textAlignment = Qt::AlignCenter;
        progressBarOption.progress = progress;
        progressBarOption.text = progress == -1 ? QString("∞") : QString ( "%1%" ).arg ( progress );
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
    mModel        = new MainAnalyseModel;
    mDelegate     = new MainAnalyseDelegate;
    mExportDialog = new QProgressDialog();
    mExportDialog->close();




    setModel(mModel);
    setItemDelegate(mDelegate);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);


    verticalHeader()->hide();

    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    horizontalHeader()->setStretchLastSection(true);

    setColumnWidth(0, 250);

    setIconSize(QSize(22,22));
    setShowGrid(false);

    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showAnalysis(QModelIndex)));


    new QShortcut(QKeySequence::Delete,this, SLOT(removeSelection()));




}

void MainAnalyseView::addFile(const QString &filename)
{
    checkFile(filename);

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

void MainAnalyseView::exportSelection(const QString &path)
{
    QModelIndexList list = selectionModel()->selectedRows();
    if (list.isEmpty())
        return;

    QProgressDialog dialog(tr("Exporting ..."), tr("Cancel"), 0, list.length(), this);
    dialog.setWindowTitle(tr("Export analysis"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setMinimumDuration(0);
    dialog.resize(300,80);
    dialog.show();
    int progress = 0;

    for ( QModelIndex index : list){

        if (dialog.wasCanceled())
            break;

        AnalysisRunner * runner = mModel->runner(index);
        if (runner->status() == AnalysisRunner::Finished)
        {
            runner->saveAll(path);
        }
        progress++;
        dialog.setValue(progress);
        QFileInfo info(runner->filename());
        dialog.setLabelText(info.fileName());
    }
}


void MainAnalyseView::dragEnterEvent(QDragEnterEvent *event)
{
    if (!event->mimeData()->hasUrls())
        return;

    event->acceptProposedAction();
}

void MainAnalyseView::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void MainAnalyseView::dropEvent(QDropEvent *event)
{
    for (QUrl url : event->mimeData()->urls())
        addFile(url.toLocalFile());

}

bool MainAnalyseView::checkFile(const QString &path)
{
    QFileInfo info(path);

    if (!info.exists())
        return false;

    if (info.size() == 0)
        return false;

    return true;
}


void MainAnalyseView::removeSelection()
{

    QList<int> rows;
    for ( QModelIndex index : selectionModel()->selectedRows()){
        rows.append(index.row());

        if (mAnalysisWidgets.contains(mModel->runner(index))){
            mAnalysisWidgets[mModel->runner(index)]->close();
            delete mAnalysisWidgets.take(mModel->runner(index));
        }

    }

    mModel->remove(rows);
}

void MainAnalyseView::stopSelection()
{
    for ( QModelIndex index : selectionModel()->selectedRows()){
        mModel->runner(index)->cancel();

        if (mAnalysisWidgets.contains(mModel->runner(index))){
            mAnalysisWidgets[mModel->runner(index)]->close();
        }

    }
}

void MainAnalyseView::clearAll()
{
    QList<int> rows;
    for (int i=0; i<mModel->rowCount(); ++i)
    {
        AnalysisRunner::Status status = mModel->runner(mModel->index(i))->status();

        if (status == AnalysisRunner::Finished || status == AnalysisRunner::Canceled)
            rows.append(i);
    }

    mModel->remove(rows);
}




