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
