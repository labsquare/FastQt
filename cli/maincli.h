#ifndef MAINCLI_H
#define MAINCLI_H

#include <QObject>
#include <QtCore>
#include "imageformatdefinition.h"
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
#include <iomanip>
using namespace std;

class MainCLI : public QEventLoop
{
    Q_OBJECT
public:
    explicit MainCLI(QCommandLineParser *parser, QObject *parent = 0);

    int exec();


protected Q_SLOTS:
    void updateInfo();
    void saveResult();

protected:
    bool checkFinish();

private:
    QCommandLineParser* mParser;
    QTimer * mTimer;
    QList<AnalysisRunner*> mRunnerList;
    ImageFormat mFormat;
};

#endif // MAINCLI_H
