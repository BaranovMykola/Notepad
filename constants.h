//************************************************************************
//    This module define all constants
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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const QString TitleName = "Notepad";
const QString TitleSeparator = " - ";
const QString AskMessage = "Do you want to save changes to";
const QString AskSeparator = " ";
const QString NotFoundMessage = "Cannot found '%1'. Matched end of the file.";
const QString ReplaceMessage = "All entrys has been replaced. Total: %1 entrys";
const QString UndefinedDirectionMessage = "Undefined direction!";
const int IntMaxLenght = 10;
const int DefaultFontSize = 9;
const QString ConfigPath = "config"; // dir in one deep with exe-file.
const QString ConfigNameFile = "config.json";
const QString TitleFullName = "%1 - Notepad";
const QString UntitiledName = "Untitled";
#endif // CONSTANTS_H
