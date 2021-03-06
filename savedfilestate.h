//************************************************************************
//    This module implement part of state pattern - behaviour of saved file
//
//    Copyright (C) 2017 Baranov Mykola <mapsg32@gmail.com>
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

#ifndef SAVEDFILESTATE_H
#define SAVEDFILESTATE_H

#include "abstractsavefilestate.h"

class SavedFileState : public AbstractSaveFileState
{
public:
    ~SavedFileState();
    void updateState(MainWindow& obj);
    void save(MainWindow&);
    void close(MainWindow& obj);
    void open(MainWindow &obj);
    void newDoc(MainWindow &obj);
private:
};

#endif // SAVEDFILESTATE_H
