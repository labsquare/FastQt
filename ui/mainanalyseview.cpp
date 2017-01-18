#include "mainanalyseview.h"

// =============== DELEGATE ============================================

void MainAnalyseDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    int lastCol = index.model()->columnCount() - 1;

    if (index.column() == lastCol)
    {
        int progress = index.data().toInt();

        if (progress == 100)
        {
            QApplication::style()->drawItemText(painter,option.rect,Qt::AlignCenter,option.palette,true,"Finished");
            return;

        }


        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;


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

    horizontalHeader()->setStretchLastSection(true);
    //horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);

}

void MainAnalyseView::addFile(const QString &filename)
{
    mModel->addFile(filename);
}




