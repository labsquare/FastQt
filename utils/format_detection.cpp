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

    @author : Pierre Marijon <pierre@marijon.fr>
*/

#include "format_detection.h"
#include <QDebug>

bool is_gz(QIODevice* file)
{
    if (file->open(QIODevice::ReadOnly))
    {
        QByteArray magic_number = file->read(2);
        file->close();

        if (magic_number.isEmpty())
            return false;

        return (unsigned char) magic_number.at(0) == 0x1f && (unsigned char) (unsigned char) magic_number.at(1) == 0x8b;
    }
    else
    {
        return false;
    }
}

bool is_bz2(QIODevice* file)
{
    if (file->open(QIODevice::ReadOnly))
    {
        QByteArray magic_number = file->read(2);
        file->close();

        if (magic_number.isEmpty())
            return false;

        return (unsigned char) magic_number.at(0) == 'B' && (unsigned char) magic_number.at(1) == 'Z';
    }
    else
    {
        return false;
    }
}

bool is_xz(QIODevice* file)
{
    if (file->open(QIODevice::ReadOnly))
    {
        QByteArray magic_number = file->read(6);
        file->close();

        if (magic_number.isEmpty())
            return false;

        return (unsigned char) magic_number.at(0) == 0xFD && (unsigned char) magic_number.at(1) == '7'\
               && (unsigned char) magic_number.at(2) == 'z' && (unsigned char) magic_number.at(3) == 'X'\
               && (unsigned char) magic_number.at(4) == 'Z' && (unsigned char) magic_number.at(5) == 0x00;
    }
    else
    {
        return false;
    }
}

bool is_fastq(QIODevice* file)
{
    if (file->open(QIODevice::ReadOnly))
    {
        QByteArray line;
        line = file->readLine();
        if (line[0] != '@')
        {
            file->close();
            return false;
        }

        line = file->readLine();
        // Some not alphabetic caractere are in range but you know isn't a problem
        if (line[0] < 'A' || line[0] > 'z')
            return false;

        line = file->readLine();
        if (line[0] != '+')
        {
            file->close();
            return false;
        }

        line = file->readLine();
        if (line[0] < '!' || line[0] > '~')
            return false;

        return true;
    }
    else
    {
        return false;
    }
}

bool is_ubam(QIODevice* file)
{
    /*Check is a gzip file*/
    if(is_gz(file))
    {
        if (file->open(QIODevice::ReadOnly))
        {
            /*Check is a bgzp file*/
            /*We use https://samtools.github.io/hts-specs/SAMv1.pdf page 10*/
            file->seek(12);
            QByteArray magic_number = file->read(3);
            file->close();

            if(magic_number.length() != 3)
                return false;

            return static_cast<unsigned char>(magic_number.at(0)) == 'B' \
                   && static_cast<unsigned char>(magic_number.at(1)) == 'C' \
                   && static_cast<unsigned char>(magic_number.at(2)) == 2;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
