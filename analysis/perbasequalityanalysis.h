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
#ifndef PERBASEQUALITYANALYSIS_H
#define PERBASEQUALITYANALYSIS_H

#include <QtCharts>
#include "analysis.h"
#include "basegroup.h"
#include "phredencoding.h"

#define QUALITY_COUNT_SIZE 150

using namespace QT_CHARTS_NAMESPACE;

class QualityCount;
/*!
 * \class PerBaseQualityAnalysis
 * \brief This view shows an overview of the range of quality values across all bases at each position in the FastQ file.
 * Relative to Per Base Sequence Quality FastQC module
 * <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/Help/3%20Analysis%20Modules/2%20Per%20Base%20Sequence%20Quality.html>
 */
class PerBaseQualityAnalysis : public Analysis
{
public:
    PerBaseQualityAnalysis();

    virtual void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;
    virtual QWidget* createResultWidget() Q_DECL_OVERRIDE;


protected:
    qreal mean(int maxbp, int minbp, int offset);
    qreal percentile(int minbp, int offset, int maxbp,int percentile);
    void computePercentages();
    QPair<char,char> computeOffsets();


private:
    QVector<qreal> means;
    QVector<qreal> medians;
    QVector<qreal> lowerQuartile;
    QVector<qreal> upperQuartile;
    QVector<qreal> lowest;
    QVector<qreal> highest;
    QVector<QString> xLabels;
    QVector<QualityCount> mQualityCounts;
    PhredEncoding mEncodingScheme;
    int mLow  = 0;
    int mHigh = 0;


};


class QualityCount {

public:
    QualityCount();
    void addValue(char c);
    qreal mean(int offset)const;
    char min()const;
    char max()const;
    qreal percentile(int offset,int percentile)const;
    int count() const;



private:
    // faster than QVector

    quint64 mCounts[QUALITY_COUNT_SIZE] = {0};
    int mTotalCounts     = 0;
};




#endif // PERBASEQUALITYANALYSIS_H
