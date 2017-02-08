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
#ifndef ANALYSISRUNNER_H
#define ANALYSISRUNNER_H
#include <QtCore>
#include <KCompressionDevice>
#include "analysis.h"
#include "fastqreader.h"
#include "imageformatdefinition.h"

/*!
 * \class AnalysisRunner
 * \brief The AnalysisRunner class read a fastq file and computes all analysis from a QThread
 * @see AnalysisRunner
 */
class Analysis;
class AnalysisRunner;
class AnalysisRunner : public QRunnable

{
public:
    enum Status {
        Waiting,
        Running,
        Canceled,
        Finished
    };

    AnalysisRunner();
    AnalysisRunner(const QString& filename);

    ~AnalysisRunner();

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

    const QString& filename() const;

    Status status() const;

    /*!
     * \brief progression of analysis in percent
     * \return value between 0 and 100
     */
    int progression() const;

    /*!
     * \brief return how many sequence has been analysed.
     * This value can be access during analysis from updated signals
     * \return number of sequence
     */
    int sequenceCount() const;



    quint64 fileSize() const;

    QString humanFileSize() const;

    const QString& lastMessage() const;

    int duration() const;

    /*!
     * \brief analysisList
     * \return all analysis avaible
     */
    const QVector<Analysis*>& analysisList() const;

    void saveAllResult(const QString& path, ImageFormat format = ImageFormat::SvgFormat);

protected:
    void emitUpdate(const QString& message);
    void setStatus(Status status);




private:
    QTime mStartTime;
    QVector<Analysis*> mAnalysisList;
    QString mFilename;
    QString mMessage;
    int mProgression = 0;
    int mSequenceCount = 0;
    int mFileSize  = 0;
    int mDuration  = 0;
    Status mStatus = Waiting;


};

#endif // ANALYSISRUNNER_H
