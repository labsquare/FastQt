#ifndef MODULE_H
#define MODULE_H
#include <QtCore>
#include <QtWidgets>
#include "sequence.h"
class Analysis
{
public:
    enum Status {
        Success , Warning, Error
    };

    Analysis();
    virtual void processSequence(const Sequence& sequence) = 0;
    virtual void reset() = 0;
    virtual QWidget* createResultWidget() = 0;


    const QString& name() const {return mName;}
    const QString& tooltip() const {return mTooltip;}

    void setName(const QString& name){mName = name;}
    void setTooltip(const QString& tooltip){mTooltip = tooltip;}

    Status status() const;
    void setStatus(const Status &status);

    QIcon statusIcon() const;

private:
    QString mName;
    QString mTooltip;
    Status mStatus;




};

#endif // MODULE_H
