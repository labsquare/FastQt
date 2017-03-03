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
#include <QApplication>
#include "mainwindow.h"
#include "perbasequalityanalysis.h"
#include "sequence.h"
#include "fastqreader.h"
#include "qfonticon.h"
#include "cliparser.h"
#include "maincli.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Fix the threads numbers
//    QThreadPool::globalInstance()->setMaxThreadCount(2);


    a.setApplicationName("FastQt");
    a.setOrganizationName("Labsquare");
    a.setOrganizationDomain("labsquare.org");
    a.setApplicationVersion("0.2.2");

    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    translator.load(QString("translations/fastqc_")+locale);
    a.installTranslator(&translator);

    qRegisterMetaType<Sequence>();

    QFontIcon::addFont(":/fonts/fontawesome.ttf");

    QCommandLineParser parser;
    populateCLIParser(parser);

    parser.process(a);

    if(parser.positionalArguments().empty())
    {
        MainWindow window;
        window.show();

        return a.exec();
    }

    else
    {
        MainCLI cli(&parser);
        cli.exec();

    }

    return 0;
}
