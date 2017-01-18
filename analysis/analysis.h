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
#ifndef MODULE_H
#define MODULE_H
#include <QtCore>
#include <QtWidgets>
#include <QtSvg/QSvgGenerator>
#include "qfonticon.h"
#include "sequence.h"

/*!
 * \class Analysis
 * \brief Analysis is the base class for all analysis
 * Create a new class inherites from Analysis and define the following methods :
 * - processSequence(const Sequence& sequence)
 * - reset()
 * - createResultWidget()
 */

class Analysis : public QObject
{
    Q_OBJECT
public:
    enum Status {
        Success , Warning, Error
    };

    Analysis(QObject * parent = Q_NULLPTR);

    virtual ~Analysis();
    /*!
     * \brief process each sequence
     * Each sequence readed from fastq file are process here one by one
     * \arg Sequence : a Sequence object
     */
    virtual void processSequence(const Sequence& sequence) = 0;
    /*!
     * \brief reset analysis
     * This methods is called when an analysis need to be recomputed from start
     */
    virtual void reset() = 0;
    /*!
     * \brief create result widget
     * Return result as a Widget based class, like a QChart
     * \return QWidget
     */
    virtual QWidget* createResultWidget() = 0;

    /*!
     * \brief save resultsWidget as image or svg
     *  \return QPixmap
     */
    void saveResult(const QString& filename);

    /*!
     * \brief toJson
     * \return serialisation as Json
     *  By default do nothing
     */
    virtual QJsonObject toJson()const;

    /*!
     * \brief fromJson
     * \param set analysis from json serialization data
     * By default do nothing
     */
    virtual void fromJson(const QJsonObject& data);

    const QString& name() const {return mName;}
    const QString& description() const {return mDescription;}

    void setName(const QString& name){mName = name;}
    void setDescription(const QString& description){mDescription = description;}



    // Not yet used
    Status status() const;
    void setStatus(const Status &status);

    QIcon statusIcon() const;

private:
    QString mName;
    QString mDescription;
    Status mStatus;
};

#endif // MODULE_H
