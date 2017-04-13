#ifndef MAINCLI_H
#define MAINCLI_H

#include <QObject>
#include <QtCore>
#include <iostream>
#include <iomanip>

#include "analysisrunner.h"
#include "imageformatdefinition.h"

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
