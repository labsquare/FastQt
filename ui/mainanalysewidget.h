#ifndef ANALYSETABWIDGET_H
#define ANALYSETABWIDGET_H

#include <QtWidgets>
#include <QtConcurrent>
#include "analysisrunner.h"
#include "basicstatsanalysis.h"

class MainAnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainAnalyseWidget(const QString& filename, QWidget *parent = 0);


public Q_SLOTS:
    void launch();
    void analysisStarted();
    void analysisUpdated(int seqCount, int percent);
    void analysisFinished();


protected :
    void clearResults();

private:

    QStackedLayout * mMainLayout;

    QLabel * mProgressLabel;
    QSplitter * mResultWidget;
    QString mFilename;
    AnalysisRunner mRunner;


    QListWidget * mListWidget;
    QStackedWidget * mStackWidget;



};

#endif // ANALYSETABWIDGET_H
