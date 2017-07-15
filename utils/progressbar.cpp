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

    Freely inspired by GATB-Core Progress class https://github.com/GATB/gatb-core
*/

#include "progressbar.h"

ProgressBar::ProgressBar(unsigned int ntasks, const std::string& message, std::ostream& output) : message(message), os(output)
{
    reset(ntasks);
}

void ProgressBar::reset(unsigned int ntasks)
{
    this->todo = ntasks;
    this->done = 0;
    this->partial = 0;
    this->subdiv = 100;
    this->steps = static_cast<double>(ntasks > 0 ? ntasks : 1) / static_cast<double>(subdiv);
}

void ProgressBar::init()
{
    os << message;
    postInit();
}

void ProgressBar::finish()
{
    /** We set the total done. */
    set (todo);

    /** We forward the remaining of the finish to postFinish method. */
    postFinish ();

    /** We reset all progression variables. */
    todo    = 0;
    done    = 0;
    partial = 0;
}

void ProgressBar::inc (unsigned int ntasks_done)
{
    done    += ntasks_done;
    partial += ntasks_done;

    while (partial >= steps)
    {
        update();
        partial -= steps;
    }
}

void ProgressBar::set (unsigned int ntasks_done)
{
    if (ntasks_done > done)
    {
        inc (ntasks_done-done);
    }
}

void ProgressBar::postInit ()
{
    os << "[";
    os.flush();
}

void ProgressBar::postFinish ()
{
    os << "]" << std::endl;
    os.flush();
}

void ProgressBar::update()
{
    os << "-";
    os.flush();
}
