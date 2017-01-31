//************************************************************************
//    This module implement basic function saving opening file
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

#ifndef SAVEFILEFUNCTION_H
#define SAVEFILEFUNCTION_H

class QFile;
class QString;

#include <QDir>

QString saveAs(QString path = QDir::homePath());

void saveFileFunction(QFile& file, QString& data);
QString openFileFunction(QFile& file);

#endif // SAVEFILEFUNCTION_H
