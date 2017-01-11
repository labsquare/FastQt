#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mTabWidget = new QTabWidget;
    setCentralWidget(mTabWidget);

    setMenuBar(new QMenuBar());

    QMenu * fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(tr("Open file"),this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("Close"),qApp, SLOT(closeAllWindows()), QKeySequence::Close);



    addToolBar("Open")->addAction("Open", this, SLOT(openFile()));

    resize(600,400);



}

MainWindow::~MainWindow()
{

}

void MainWindow::addFile(const QString &filename)
{

    MainAnalyseWidget * w = new MainAnalyseWidget(filename);
    mainList.append(w);
    mTabWidget->addTab(w, w->windowIcon(), w->windowTitle());

}

void MainWindow::run()
{

    addFile("/home/sacha/merge.fastq");
    mainList.first()->launch();

}

void MainWindow::openFile()
{


    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Fastq file"), QDir::homePath(), tr("Fastq Files (*.fastq)"));

    if (!fileName.isEmpty())
    {
        addFile(fileName);
        mainList.first()->launch();
    }


}



