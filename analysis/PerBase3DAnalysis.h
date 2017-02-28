#ifndef PERBASE3DANALYSIS_H
#define PERBASE3DANALYSIS_H
#include "analysis.h"
#include <QtDataVisualization>
using namespace QtDataVisualization;


class PerBase3DAnalysis : public Analysis
{
public:
    PerBase3DAnalysis(QObject * parent = Q_NULLPTR);

    virtual void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual QWidget* createResultWidget() Q_DECL_OVERRIDE;


};

#endif // PERBASE3DANALYSIS_H
