#include "PerBase3DAnalysis.h"

PerBase3DAnalysis::PerBase3DAnalysis(QObject *parent)
    :Analysis(parent)
{

}

void PerBase3DAnalysis::processSequence(const Sequence &sequence)
{

}

void PerBase3DAnalysis::reset()
{

}

QWidget *PerBase3DAnalysis::createResultWidget()
{

    Q3DSurface * surface = new Q3DSurface;
    surface->setFlags(surface->flags() ^ Qt::FramelessWindowHint);

    QSurfaceDataArray *data = new QSurfaceDataArray;
    QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
    QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;

    *dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
    *dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);
    *data << dataRow1 << dataRow2;

    QSurface3DSeries *series = new QSurface3DSeries;
    series->dataProxy()->resetArray(data);
    surface->addSeries(series);


    return QWidget::createWindowContainer(surface);

}
