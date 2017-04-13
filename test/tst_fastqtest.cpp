#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "analysisrunner.h"
#include "format_detection.h"

class FastqTest : public QObject
{
    Q_OBJECT

public:
    FastqTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void analyse();
    void analyse_data();

private:
    AnalysisRunner * mRunner;


};

FastqTest::FastqTest(){}

void FastqTest::init()
{
    mRunner = new AnalysisRunner;
}

void FastqTest::cleanup()
{
    delete mRunner;
}

void FastqTest::analyse_data()
{
    QTest::addColumn<QString>("path");
    QTest::newRow("path") <<"/home/sacha/test.fastq";
    QTest::newRow("path") <<"/home/sacha/yves.db";
}


void FastqTest::analyse()
{
    QFETCH(QString, path);

    QFile file(path);
    QVERIFY2(file.exists(), qPrintable(path + " doesn't exists"));
    mRunner->setFilename(path);
    mRunner->run();

}

QTEST_MAIN(FastqTest)

#include "tst_fastqtest.moc"
