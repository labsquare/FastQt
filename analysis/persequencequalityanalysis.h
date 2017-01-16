/*
Copyright Copyright 2016-17 Sacha Schutz

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
#ifndef PERSEQUENCEQUALITYANALYSIS_H
#define PERSEQUENCEQUALITYANALYSIS_H

#include <QtCore>
#include <QtCharts>
#include "analysis.h"

using namespace QT_CHARTS_NAMESPACE;
/*!
 * \class PerSequenceQualityAnalysis
 * \brief The per sequence quality score report allows you to see if a subset of your sequences have universally low quality values.
 * Relative to Per Sequence Quality Scores Scores FastQC module
 * <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/Help/3%20Analysis%20Modules/3%20Per%20Sequence%20Quality%20Scores.html>
 */
class PerSequenceQualityAnalysis : public Analysis
{
public:
    PerSequenceQualityAnalysis(QObject * parent = Q_NULLPTR);

    virtual void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual QWidget* createResultWidget()Q_DECL_OVERRIDE;


private:
QHash<int, quint64> mAverageScoreCounts;

};

#endif // PERSEQUENCEQUALITYANALYSIS_H
