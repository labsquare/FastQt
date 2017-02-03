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

class MainCLI : public QObject
{
    Q_OBJECT
public:
    explicit MainCLI(QCommandLineParser *parser, QObject *parent = 0);

    int exec();

signals:

public slots:

private:
    QCommandLineParser* mParser;
};

#endif // MAINCLI_H
