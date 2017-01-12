/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of CuteVCF.

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
#ifndef ANALYSISRUNNER_H
#define ANALYSISRUNNER_H
#include <QtCore>
#include <KCompressionDevice>
#include "analysis.h"
#include "fastqreader.h"


/*!
 * \class AnalysisRunner
 * \brief The AnalysisRunner class read a fastq file and computes all analysis from a QThread
 * @see AnalysisRunner
 */
class AnalysisRunner : public QThread
{
    Q_OBJECT
public:
    AnalysisRunner(QObject * parent = 0);
    AnalysisRunner(const QString& filename, QObject * parent = 0);

    /*!
     * \brief run all analyis asynchronously
     */
    virtual void run() Q_DECL_OVERRIDE;
    /*!
     * \brief add Analysis
     * \param Analysis: analysis
     */
    void addAnalysis(Analysis* analysis);
    /*!
     * \brief set fastq file path
     * \param QString: file path
     */
    void setFilename(const QString& filename);
    /*!
     * \brief reset all analysis
     */
    void reset();

    /*!
     * \brief analysisList
     * \return all analysis avaible
     */
    const QVector<Analysis*>& analysisList() const;

Q_SIGNALS:
    void updated(QString message);


private:
    QVector<Analysis*> mAnalysisList;
    QString mFilename;

};

#endif // ANALYSISRUNNER_H
