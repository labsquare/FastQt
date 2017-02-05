#ifndef MAINANALYSEMODEL_H
#define MAINANALYSEMODEL_H
#include <QAbstractListModel>
#include <QSignalMapper>
#include "qfonticon.h"
#include "analysisrunner.h"
#include "basicstatsanalysis.h"
#include "perbasequalityanalysis.h"
#include "persequencequalityanalysis.h"
#include "perbasecontentanalysis.h"
#include "overrepresentedseqsanalysis.h"
#include "perbasencontentanalysis.h"
#include "persequencegccontent.h"
#include "lengthdistributionanalysis.h"

class MainAnalyseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        NameColumn = 0,
        StatusColumn,
        SizeColumn,
        ProgressColumn,
        ReadsColumn,
        TimeColumn
    };
    MainAnalyseModel(QObject * parent = Q_NULLPTR);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())Q_DECL_OVERRIDE;

    void addFile(const QString& filename);
    AnalysisRunner * runner(const QModelIndex& index);

protected Q_SLOTS:
    void updated(int row);
    void timeUpdated();


private:
    QList<AnalysisRunner*> mRunners;
    QSignalMapper *mSignalMapper;
    QTimer * mTimer;

};

#endif // MAINANALYSEMODEL_H
