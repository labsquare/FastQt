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

#include "cliparser.h"

void populateCLIParser(QCommandLineParser &parser)
{
    parser.setApplicationDescription("FastQt");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("files", QCoreApplication::translate("files", "List of fastq files"), "[files...]");

    QCommandLineOption outputOption(QStringList() << "o" << "outdir",
                                    QCoreApplication::tr("Create all output files in the specified output directory. Please note that this directory must exist as the program will not create it.  If this option is not set then the output file for each sequence file is created in the same directory as the sequence file which was processed."),
                                    "outdir");

    QCommandLineOption threadOption(QStringList() << "t" << "threads",
                                    QCoreApplication::tr("Specifies the number of files which can be processed simultaneously. Use by default all avaible CPU"),
                                    "threads");
    QCommandLineOption citeOption("cite",
                                       QCoreApplication::tr("Get in bibtex format to cite FastQt"));

//    QCommandLineOption outImgFormatOption(QStringList() << "out-img-format",
//                                          QCoreApplication::tr("Specifies the format image output. By default value is \"svg\". Possible value is \"svg\" and \"png\"."),
//                                          "outimgformat",
//                                          "svg");


    parser.addOption(outputOption);
    parser.addOption(threadOption);
    parser.addOption(citeOption);
//    parser.addOption(outImgFormatOption);
}
