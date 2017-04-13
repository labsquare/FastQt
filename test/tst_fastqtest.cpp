#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "analysisrunner.h"

class FastqTest : public QObject
{
    Q_OBJECT

public:
    FastqTest();

private Q_SLOTS:
    void open();

private:
    AnalysisRunner * mRunner;

};

FastqTest::FastqTest()
{
    mRunner = new AnalysisRunner;
}

void FastqTest::open()
{


    QVERIFY2(true, "Failure");
}

QTEST_MAIN(FastqTest)

#include "tst_fastqtest.moc"
