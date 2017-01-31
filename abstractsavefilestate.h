//************************************************************************
//    This module implement abstract class of state pattern
//
//    Copyright (C) 2017 Baranov Mykola
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>
//************************************************************************


#ifndef ABSTRACTFILESTATE_H
#define ABSTRACTFILESTATE_H

class MainWindow;

class AbstractSaveFileState
{
public:
    virtual ~AbstractSaveFileState(){};
    virtual void updateState(MainWindow& obj)=0;
    virtual void save(MainWindow& obj)=0;
    virtual void close(MainWindow& obj)=0;
    virtual void open(MainWindow& obj)=0;
    virtual void newDoc(MainWindow& obj)=0;
private:
};

#endif // ABSTRACTFILESTATE_H
