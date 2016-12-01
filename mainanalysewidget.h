#ifndef ANALYSETABWIDGET_H
#define ANALYSETABWIDGET_H

#include <QtWidgets>
#include <QtConcurrent>
#include "fastqreader.h"
#include "abstractanalysewidget.h"

#include "statanalysewidget.h"

class MainAnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainAnalyseWidget(const QString& filename, QWidget *parent = 0);

    void addAnalyse(AbstractAnalyseWidget * widget);
    void runAllAnalysis();






Q_SIGNALS:
    void started();
    void updated(const Sequence& sequence);
    void finished();

protected:




private:
    QListWidget * mListWidget;
    QStackedWidget * mStackedWidget;
    QString mFilename;

    QList<AbstractAnalyseWidget*> mAnalyisis;


};

#endif // ANALYSETABWIDGET_H
