/*
Copyright 2016-17 Sacha Schutz

    This file is part of FastQt.

    FastQt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastQt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastQt.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "analysis.h"
Analysis::Analysis(QObject * parent)
    :QObject(parent)
{
    mParentRunner = Q_NULLPTR;
}

Analysis::~Analysis()
{

}

void Analysis::save(const QString &path)
{
    QString name = metaObject()->className();
    QDir dir(path);
    QString svgPath = dir.filePath(QString("%1.svg").arg(name));
    QString pngPath = dir.filePath(QString("%1.png").arg(name));

    capture(svgPath);
    capture(pngPath, ImageFormat::PngFormat);
}


void Analysis::capture(const QString &filename, ImageFormat format)
{
    if (format == SvgFormat)
    {
        QSvgGenerator generator;
        generator.setFileName(filename);
        generator.setTitle(name());
        generator.setDescription(description());
        createResultWidget()->render(&generator);

    }

    else {
        if (!createResultWidget()->grab().save(filename))
            qWarning()<<Q_FUNC_INFO<<"cannot save "<<filename;
    }

}


AnalysisRunner *Analysis::runner() const
{
    return mParentRunner;
}

void Analysis::setRunner(AnalysisRunner *runner)
{
    mParentRunner = runner;
}

Analysis::Status Analysis::status() const
{
    return Analysis::Unknown;
}

QIcon Analysis::statusIcon() const
{
    // @see http://fontawesome.io/icons/ to get font hex number
    if (status() == Analysis::Success)
        return QFontIcon::icon(0xf05d, QColor("#71E096"));
    if (status() == Analysis::Warning)
        return QFontIcon::icon(0xf06a, QColor("#F5A26F"));
    if (status() == Analysis::Error)
        return QFontIcon::icon(0xf057, QColor("#ED6D79"));

    //Unknown
    return QFontIcon::icon(0xf05d, qApp->palette("QWidget").highlight().color());

}
