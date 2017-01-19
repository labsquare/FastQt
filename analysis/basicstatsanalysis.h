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
#ifndef BASICSTATSANALYSIS_H
#define BASICSTATSANALYSIS_H
#include <limits>
#include <QtCore>
#include <QLocale>
#include "analysis.h"
#include  "keyvaluemodel.h"
#include "phredencoding.h"

/*!
 * \class BasicStatsAnalysis
 * \brief he Basic Statistics module generates some simple composition statistics for the file analysed.
 * Relative to Basic Statistics FastQC module
 * <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/Help/3%20Analysis%20Modules/1%20Basic%20Statistics.html>
 */

class BasicStatsAnalysis : public Analysis
{
    Q_OBJECT
    Q_PROPERTY(int readCount READ readCount)

public:
    BasicStatsAnalysis(QObject * parent = Q_NULLPTR);
    void processSequence(const Sequence& sequence) Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
    QWidget * createResultWidget() Q_DECL_OVERRIDE;

    int readCount();

private:
    QString mEncoding;
    int mReadCount   = 0;
    int mMinLength   = std::numeric_limits<int>::max();
    int mMaxLength   = 0;
    quint64 mGCount  = 0;
    quint64 mCCount  = 0;
    quint64 mACount  = 0;
    quint64 mTCount  = 0;
    quint64 mNCount  = 0;
    quint64 mXCount  = 0;


    char mLowestChar = 126;
    quint64* count[256];
};

#endif // BASICSTATSANALYSIS_H
