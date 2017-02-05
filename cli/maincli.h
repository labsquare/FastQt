#ifndef MAINCLI_H
#define MAINCLI_H

#include <QObject>
#include <QtCore>

#include "analysisrunner.h"
#include "basicstatsanalysis.h"
#include "perbasequalityanalysis.h"
#include "persequencequalityanalysis.h"
#include "perbasecontentanalysis.h"
#include "overrepresentedseqsanalysis.h"
#include "perbasencontentanalysis.h"
#include "persequencegccontent.h"
#include "lengthdistributionanalysis.h"
#include <iostream>

using namespace std;

class MainCLI : public QEventLoop
{
    Q_OBJECT
public:
    explicit MainCLI(QCommandLineParser *parser, QObject *parent = 0);

    int exec();


protected Q_SLOTS:
    void showProgression();

private:
    QCommandLineParser* mParser;
    QTimer * mTimer;
    QList<AnalysisRunner*> mRunnerList;


};

#endif // MAINCLI_H
