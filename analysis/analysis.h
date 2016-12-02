#ifndef MODULE_H
#define MODULE_H
#include <QtCore>
#include <QtWidgets>
#include "sequence.h"
class Analysis
{
public:
    Analysis();
    virtual void processSequence(const Sequence& sequence) = 0;

    virtual QWidget* createResultWidget(){ new QPushButton("salut");}


    const QString& name() const {return mName;}
    const QIcon& icon() const {return mIcon;}
    void setName(const QString& name){mName = name;}
    void setIcon(const QIcon& icon){mIcon = icon;}

private:
    QString mName;
    QIcon mIcon;



};

#endif // MODULE_H
