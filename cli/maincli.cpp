#include "maincli.h"

MainCLI::MainCLI(QCommandLineParser* parser, QObject *parent) : QEventLoop(parent), mParser(parser), mFormat(ImageFormat::SvgFormat)
{
    mTimer = new QTimer(this);
    mTimer->start(1000);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(updateInfo()));

}

int MainCLI::exec()
{
    // check cite option if is set return citation in bibtex format and stop
    if (mParser->isSet("cite"))
    {
        cout<<"@misc{FastQt,"<<endl;
        cout<<"      author = {Labsquare Team et al},"<<endl;
        cout<<"      title = {FastQt: a quality control tool for high throughput sequence data.},"<<endl;
        cout<<"      year = {2017},"<<endl;
        cout<<"      publisher = {GitHub},"<<endl;
        cout<<"      journal = {GitHub repository},"<<endl;
        cout<<"      howpublished = {\\url{https://github.com/labsquare/fastQt},"<<endl;
        cout<<"      doi = {doi:10.5281/zenodo.824549}"<<endl;
        cout<<"}"<<endl;
        exit();
        return 0;
    }

    if (mParser->positionalArguments().isEmpty())
    {
        qDebug()<<"No fastq provided";
        exit();
        return 0;
    }

//    QString tmp = mParser->value("out-img-format");
//    if (mParser->value("out-img-format") == "svg")
//    {
//        mFormat = ImageFormat::SvgFormat;
//    }
//    else if (mParser->value("out-img-format") == "png")
//    {
//        mFormat = ImageFormat::PngFormat;
//    }
//    else
//    {
//        qDebug()<<mParser->value("out-img-format")<<" isn't a valid value for out-img-format, run --help option";
//        exit();
//    }

    // Set thread number
    int threadNumber;
    if (mParser->value("threads").isEmpty())
        threadNumber = QThread::idealThreadCount();
    else
        threadNumber = mParser->value("threads").toInt();

    cout<<"Starting Analysis..."<<endl;
    cout<<setw(5)<<left<<"Thread number:"<<threadNumber<<endl;
    cout<<setw(5)<<left<<"File count:"<< mParser->positionalArguments().count()<<endl;

    for(QString filename : mParser->positionalArguments())
        cout<<setw(5)<<left<<"File:"<<filename.toStdString()<<endl;


    // Set max thread number
    QThreadPool::globalInstance()->setMaxThreadCount(threadNumber);

    AnalysisRunner* runner;
    for(QString filename : mParser->positionalArguments())
    {
        runner = AnalysisRunner::createAnalysisRunner();
        runner->setFilename(filename);

        mRunnerList.append(runner);
        QFileInfo info(filename);
        cout<<"Start Analysis "<<info.fileName().toStdString()<<endl;
        QThreadPool::globalInstance()->start(runner);
    }


    return QEventLoop::exec(); // Loop until all runner has been finished
}

void MainCLI::updateInfo()
{

    for (AnalysisRunner * r : mRunnerList)
    {
        QFileInfo info(r->filename());
        if (r->status() == AnalysisRunner::Running)
            cout<<std::setw(5) << left<<"Analysis "<<info.fileName().toStdString()<<" "<<r->progression()<<" %"<<endl;
    }

    if (checkFinish()){

        saveResult();
        quit();
    }

}

void MainCLI::saveResult()
{
    QString path   = mParser->value("outdir");

    if (path.isEmpty())
    {
        QFileInfo info(mRunnerList.first()->filename());
        path = info.dir().path();
    }

    cout<<"Save results in "<< path.toStdString()<<endl;

    for (AnalysisRunner * r : mRunnerList)
    {
        QDir dir(path);
        r->saveAll(dir.path());

    }


}

bool MainCLI::checkFinish()
{

    for (AnalysisRunner * r : mRunnerList)
    {
        if (r->status() == AnalysisRunner::Running)
            return false;
    }

    return true;
}
