#ifndef ANALYSETABWIDGET_H
#define ANALYSETABWIDGET_H

#include <QtWidgets>
#include "fastqreader.h"
#include "abstractanalysewidget.h"
#include "statanalysewidget.h"

class MainAnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainAnalyseWidget(const QString& filename, QWidget *parent = 0);

public slots:
    void run();

protected:
    void addAnalyse(AbstractAnalyseWidget * widget);


private:
    FastqReader * mReader;
    QList<AbstractAnalyseWidget*> mAnalyseWidgets;
    QListWidget * mListWidget;
    QStackedWidget * mStackedWidget;



};

#endif // ANALYSETABWIDGET_H
