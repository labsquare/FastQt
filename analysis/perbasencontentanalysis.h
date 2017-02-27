/*
Copyright Copyright 2016-17 Pierre Marijon
    This file is part of fastQT.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#ifndef PERBASENCONTENTANALYSIS_H
#define PERBASENCONTENTANALYSIS_H
#include <QtCore>
#include <QtCharts>
#include "analysis.h"
#include "basegroup.h"

using namespace QT_CHARTS_NAMESPACE;
/*!
 * \class PerBaseNContentAnalysis
 * \brief Per Base Sequence Content plots out the proportion of each base position in a file for which each of N bases has been called.
 * Relative to Per Base N Content FastQC module Basic
 * <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/Help/3%20Analysis%20Modules/6%20Per%20Base%20N%20Content.html>
 */
class PerBaseNContentAnalysis : public Analysis
{
    Q_OBJECT

public:
    PerBaseNContentAnalysis(QObject * parent = Q_NULLPTR);

    virtual void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual QWidget* createResultWidget() Q_DECL_OVERRIDE;

protected:
    void computePercentages();
    virtual void after() Q_DECL_OVERRIDE;

private:
    QVector<quint64> mNCounts;
    QVector<quint64> mXCounts;

    QVector<qreal> nPercent;

    QVector<QString> mXCategories;
    QVector<quint64>* counts[256];
};

#endif // PERBASENCONTENTANALYSIS_H
