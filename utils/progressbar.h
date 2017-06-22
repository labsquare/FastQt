/*
Copyright Copyright 2016-17 Pierre Marijon

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
    @author : Pierre Marijon <pierre@marijon.fr>

    Freely inspired by GATB-Core Progress class https://github.com/GATB/gatb-core
*/

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>

class ProgressBar
{
public:
    ProgressBar(unsigned int ntask, const std::string& message, std::ostream& os=std::cerr);

    virtual ~ProgressBar() {}

    void init();

    void finish();

    void inc(unsigned int ntask_done);

    void set(unsigned int ntask_done);

    void reset(unsigned int ntask);

protected:

protected:

    virtual void update     ();
    virtual void postInit   ();
    virtual void postFinish ();

    std::string message;
    u_int64_t     done;
    u_int64_t     todo;
    int           subdiv ; // progress printed every 1/subdiv of total to do
    double        partial;
    double        steps ; //steps = _todo/subidv
    std::ostream& os;
    char buffer[512];
};

#endif // PROGRESSBAR_H
