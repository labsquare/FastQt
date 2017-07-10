/*
Copyright 2016-17 Pierre Marijon

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

    @author : Pierre Marijon <pierre@marijon.fr>
*/

#ifndef FORMAT_DETECTION_H
#define FORMAT_DETECTION_H

#include <QIODevice>

bool is_gz(QIODevice* file);

bool is_bz2(QIODevice* file);

bool is_xz(QIODevice* file);

bool is_fastq(QIODevice* file);

#endif // FORMAT_DETECTION_H
