/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

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
#ifndef ANALYSETABWIDGET_H
#define ANALYSETABWIDGET_H

#include <QtWidgets>
#include <QtConcurrent>
#include "analysisrunner.h"
#include "basicstatsanalysis.h"
#include "perbasequalityanalysis.h"
#include "persequencequalityanalysis.h"
#include "perbasecontentanalysis.h"
#include "overrepresentedseqsanalysis.h"
#include "perbasencontentanalysis.h"
#include "persequencegccontent.h"
#include "lengthdistributionanalysis.h"

 /** \class MainAnalyseWidget
 * \brief TabWidget witch encapsulate AnalysisRunner and display AnalysisRunner::resultWidget
 * @see Analysis
 */
class MainAnalyseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainAnalyseWidget( QWidget *parent = 0);
    ~MainAnalyseWidget();


    void setRunner(AnalysisRunner * runner);

private:
    QToolBar * mToolBar;
    QVBoxLayout * mMainLayout;
    QSplitter * mResultWidget;
    AnalysisRunner * mRunner;
    QListWidget * mListWidget;
    QStackedWidget * mStackWidget;



};

#endif // ANALYSETABWIDGET_H
