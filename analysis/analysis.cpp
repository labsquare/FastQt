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
#include "analysis.h"
Analysis::Analysis()
{
    mStatus = Analysis::Success;
}

Analysis::Status Analysis::status() const
{
    return mStatus;
}

void Analysis::setStatus(const Status &status)
{
    mStatus = status;
}

QIcon Analysis::statusIcon() const
{
    // @see http://fontawesome.io/icons/ to get font hex number
//    if (mStatus == Analysis::Success)
//        return QFontIcon::icon(0xf058);
//    if (mStatus == Analysis::Error)
//         return QFontIcon::icon(0xf058);
//    if (mStatus == Analysis::Warning)
//         return QFontIcon::icon(0xf058);

    return QFontIcon::icon(0xf058,qApp->palette("QWidget").highlight().color());

}

