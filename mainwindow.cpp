//************************************************************************
//    This module implement definition of MainWindow class
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextDocument>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCursor>
#include <iterator>
#include <QDate>
#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QPrintDialog>
#include <QProgressDialog>
#include <QPrinterInfo>

#include <map>

#include "abstractsavefilestate.h"
#include "unsavedfilestate.h"
#include "savedfilestate.h"
#include "savefilefunction.h"

#include "ui_finddialog.h"
#include "ui_gotodialog.h"
#include "ui_fontdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    findMenu(0),
    replaceMenu(0),
    mGoToMenu(0),
    mFontMenu(0),
    mFontLoaded(false),
    mAboutMenu(0)
{
    stateSave = new SavedFileState;
    ui->setupUi(this);

    findMenu.setMemo(ui->memo);
    replaceMenu.setFindDialog(&findMenu);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotOpenFile()), Qt::UniqueConnection);
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(slotSaveFile()), Qt::UniqueConnection);
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(slotClose()), Qt::UniqueConnection);
    connect(ui->memo, SIGNAL(textChanged()), this, SLOT(slotEdit()), Qt::UniqueConnection);
    connect(ui->actionSave_as, SIGNAL(triggered(bool)), this, SLOT(slotSaveAs()), Qt::UniqueConnection);
    connect(ui->actionDelete, SIGNAL(triggered(bool)), this, SLOT(slotDeleteSelected()), Qt::UniqueConnection);
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(slotFind()), Qt::UniqueConnection);
    connect(ui->actionFind_next, SIGNAL(triggered(bool)), this, SLOT(slotFindNext()), Qt::UniqueConnection);
    connect(findMenu.ui->whatFind, SIGNAL(editingFinished()), this, SLOT(slotEditFindWord()), Qt::UniqueConnection);
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(slotNewFile()), Qt::UniqueConnection);
    connect(ui->actionReplace, SIGNAL(triggered(bool)), this, SLOT(slotReplace()), Qt::UniqueConnection);
    connect(ui->actionGo_to, SIGNAL(triggered(bool)), this, SLOT(slotGoTo()), Qt::UniqueConnection);
    connect(ui->actionTime_Date, SIGNAL(triggered(bool)), this, SLOT(slotInserData()), Qt::UniqueConnection);
    connect(ui->actionFont, SIGNAL(triggered(bool)), this, SLOT(slotFont()), Qt::UniqueConnection);
    connect(ui->actionWord_Wrap, SIGNAL(triggered(bool)), this, SLOT(slotWordWrap()), Qt::UniqueConnection);
    connect(ui->actionStatus_Bar, SIGNAL(triggered(bool)), this, SLOT(slotStatusBar()), Qt::UniqueConnection);
    connect(ui->actionAbout_Notepad, SIGNAL(triggered(bool)), this, SLOT(slotAbout()), Qt::UniqueConnection);
    connect(ui->actionPrint, SIGNAL(triggered(bool)), this, SLOT(slotPrint()), Qt::UniqueConnection);
    connect(ui->actionSelect_all, SIGNAL(triggered(bool)), this, SLOT(slotSelectAll()), Qt::UniqueConnection);
    connect(ui->actionPage_Option, SIGNAL(triggered(bool)), this, SLOT(slotPageOption()), Qt::UniqueConnection);

    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionExit->setShortcut(QKeySequence::Close);
    ui->actionFind->setShortcut(QKeySequence::Find);
    ui->actionFind_next->setShortcut(QKeySequence::FindNext);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    ui->actionUndo_2->setShortcut(QKeySequence::Undo);
    ui->actionDelete->setShortcut(QKeySequence::Delete);
    ui->actionPaste->setShortcut(QKeySequence::Paste);
    ui->actionCut_2->setShortcut(QKeySequence::Cut);
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionReplace->setShortcut(QKeySequence::Replace);
    ui->actionGo_to->setShortcut(QKeySequence::Forward);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionTime_Date->setShortcut(QKeySequence("Ctrl+D"));
    ui->actionSave_as->setShortcut(QKeySequence("Alt+Ctrl+S"));
    ui->actionSelect_all->setShortcut(QKeySequence::SelectAll);
    ui->actionPrint->setShortcut(QKeySequence::Print);

    readConfigFrom(ConfigPath, ConfigNameFile);

}

MainWindow::~MainWindow()
{
    saveConfigTo(ConfigPath, ConfigNameFile);
    delete stateSave;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    qDebug() << "state saved: " << (dynamic_cast<UnsavedFileState*>(stateSave) == nullptr);
    if(dynamic_cast<UnsavedFileState*>(stateSave) == nullptr)
    {
        event->accept();
    }
    else
    {
        //event->ignore(); //prevent for closing after asking :D
        slotClose();
        if(dynamic_cast<UnsavedFileState*>(stateSave) == nullptr)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}

void MainWindow::updateCaption()
{
    QString name = UntitiledName;
    if(!mFile.fileName().isEmpty())
    {
        name = mFile.fileName();
    }
    this->setWindowTitle(TitleFullName.arg(name));
}

void MainWindow::slotOpenFile()
{
    stateSave->open(*this);
}

void MainWindow::slotNewFile()
{
    stateSave->newDoc(*this);
    updateCaption();
}

void MainWindow::slotSaveFile()
{
    stateSave->save(*this);
}

bool MainWindow::slotSaveAs()
{
    QString fileName = saveAs(lastDir);
    if(!fileName.isEmpty())
    {
        mFile.setFileName(fileName);
        auto data = getPlainText();
        saveFileFunction(mFile, data);
        ui->statusBar->showMessage(QString("File saved as %1").arg(mFile.fileName()));
    }
    else
    {
        ui->statusBar->showMessage(QString("File wasn't saved"));
    }
    updateCaption();
    lastDir = fileName;
    return !fileName.isEmpty();
}

void MainWindow::slotClose()
{
    stateSave->close(*this);
}

void MainWindow::slotEdit()
{
    if(dynamic_cast<UnsavedFileState*>(stateSave) == nullptr)
    {
        stateSave->updateState(*this);
        ui->statusBar->showMessage(QString("File get unsaved changes"));
    }
    bool enable = !ui->memo->toPlainText().isEmpty();
    ui->actionFind->setEnabled(enable);
    ui->actionSelect_all->setEnabled(enable);
}

void MainWindow::slotDeleteSelected()
{
    auto cursor = ui->memo->textCursor();
    QString etc;
    QString selected = cursor.selectedText();
    if(cursor.selectedText().length() > 30)
    {
        etc = "...";
        selected.resize(30);
    }
    ui->statusBar->showMessage(tr("Selected text (%1%2) has been removed").arg(selected).arg(etc));
    cursor.removeSelectedText();
    ui->memo->setTextCursor(cursor);
}

void MainWindow::slotFind()
{
    findMenu.show();
    findMenu.activateWindow();
}

void MainWindow::slotFindNext()
{
    findMenu.slotFindNext();
}

void MainWindow::slotEditFindWord()
{
    ui->actionFind_next->setEnabled(!findMenu.ui->whatFind->text().isEmpty());
}

void MainWindow::slotReplace()
{
    replaceMenu.show();
    replaceMenu.activateWindow();
}

void MainWindow::slotGoTo()
{
    if(QDialog::Accepted == mGoToMenu.exec())
    {
        auto pointer = ui->memo->textCursor();
        pointer.setPosition(0);
        pointer.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, mGoToMenu.ui->line->text().toInt());
        ui->memo->setTextCursor(pointer);
    }
    ui->statusBar->showMessage(tr("Moving cursor to %1th line").arg(QString::number(mGoToMenu.ui->line->text().toInt()+1)));
}

void MainWindow::slotInserData()
{
    auto pointer = ui->memo->textCursor();
    pointer.insertText(QString("%1 - %2").arg(QDate::currentDate().toString()).arg(QTime::currentTime().toString()));
    ui->memo->setTextCursor(pointer);
    ui->statusBar->showMessage("Inserted current time and date");
}

void aFunction()
{

}

void MainWindow::slotFont()
{
    if(!mFontLoaded)
    {
        mFontMenu.populateFonts();
        mFontMenu.updateSelectedFonts(ui->memo->font(), mStyleName);
        mFontLoaded = true;
    }
    if(QDialog::Accepted == mFontMenu.exec())
    {
        ui->memo->setFont(mFontMenu.getFont());
        mStyleName = mFontMenu.getSelectedLabel(mFontMenu.ui->styleList)->text();
    }
}

void MainWindow::slotWordWrap()
{
    QString dis;
    if(ui->actionWord_Wrap->isChecked())
    {
        ui->memo->setWordWrapMode(QTextOption::WordWrap);
    }
    else
    {
        ui->memo->setWordWrapMode(QTextOption::NoWrap);
        dis = "dis";
    }
    ui->statusBar->showMessage(tr("Word wrapping %1enabled").arg(dis));
}

void MainWindow::slotStatusBar()
{
    ui->statusBar->setVisible(ui->actionStatus_Bar->isChecked());
}

void MainWindow::slotAbout()
{
    mAboutMenu.exec();
}



void MainWindow::slotPageOption()
{
    QPageSetupDialog setup(&printer, this);
    setup.exec();
}

void MainWindow::slotPrint()
{
    QPrintPreviewDialog *pd = new QPrintPreviewDialog(&printer);
    connect(pd,SIGNAL(paintRequested(QPrinter*)),this,SLOT(slotPrintFile(QPrinter*)));
    pd->exec();
}

void MainWindow::slotPrintFile(QPrinter *p)
{
    QTextDocument doc(getPlainText(), this);
    doc.setDefaultFont(ui->memo->font());
    doc.print(p);
//    qDebug() << "From " <<  p->fromPage() << "to " << p->toPage() << "pages";
//    int c = p->fromPage();
//    QProgressDialog progress(tr("Printig..."), tr("Abort"), c, p->toPage());
//    if(p->toPage() != 0)
//    {
//        progress.exec();
//    }
//    while(c++ < p->toPage())
//    {
//        if(progress.wasCanceled())
//        {
//            break;
//        }
//        progress.setValue(p->toPage()-c);
////        p->newPage();
//    }
}

void MainWindow::slotSelectAll()
{
    auto cursor = ui->memo->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    ui->memo->setTextCursor(cursor);
}

void MainWindow::saveConfigTo(const QString &path, const QString& file)
{
    QDir dir = qApp->applicationDirPath();
    QString localPath = dir.absolutePath();
    qDebug() << localPath;
    localPath = localPath.append("/%1").arg(path);
    QDir localDir(localPath);
    qDebug() << localDir.absolutePath();
    if(!localDir.exists())
    {
       localDir.mkdir(localDir.path());
    }
    QFile config(localDir.path().append("/%1").arg(file));
    writeJsonConfig(config);
}

void MainWindow::openFile(QString fileName)
{
    mFile.setFileName(fileName);
    QString data = openFileFunction(mFile);
    ui->memo->setPlainText(data);
    stateSave->updateState(*this);
    updateCaption();
}

void MainWindow::open()
{
    QFileDialog files;
    if(lastDir.isEmpty())
    {
        lastDir = QDir::homePath();
    }
    mPathFile = QFileDialog::getOpenFileName(this, tr("Open File..."), lastDir, "Text Files (*.txt);; All Files (*.*)");
    if(!mPathFile.isEmpty())
    {
        openFile(mPathFile);
        lastDir = mPathFile;
    }
}

void MainWindow::save()
{
    //mFile.write(arr);
}

void MainWindow::erase()
{
    ui->memo->clear(); //edited -> unsavedstate
    stateSave->updateState(*this); //setup savedstate
}

void MainWindow::updateTitle(QString newTitle)
{
    setWindowTitle(newTitle+TitleSeparator+TitleName);
}

QString MainWindow::getPlainText()
{
    return ui->memo->toPlainText();
}

QFont MainWindow::readFont(QJsonObject fontObject)
{
    auto data = readQJsonObject(fontObject);
    mStyleName = std::get<DataType::String>(data)["Style"];
    QFontDatabase base;
    return base.font(std::get<DataType::String>(data)["Family"],
            mStyleName,
            static_cast<int>(std::get<DataType::Double>(data)["Size"]));
}

bool MainWindow::readWordWrap(QJsonObject obj) const
{
    auto data = readQJsonObject(obj);
    return std::get<DataType::Bool>(data)["checked"];
}

bool MainWindow::readStatusBar(QJsonObject obj) const
{
    auto data = readQJsonObject(obj);
    return std::get<DataType::Bool>(data)["checked"];
}

QString MainWindow::readPath(QJsonObject obj) const
{
    auto data = readQJsonObject(obj);
    return std::get<DataType::String>(data)["dir"];
}

std::tuple<std::map<QString, QString>, std::map<QString, double>, std::map<QString, bool> > MainWindow::readQJsonObject(QJsonObject obj) const
{
    std::map<QString, QString> valueStr;
    std::map<QString, double> valueDouble;
    std::map<QString, bool> valueBool;
    auto jsonData = make_tuple(valueStr, valueDouble, valueBool);

    QStringList keys = obj.keys();
    int indexKey = 0;
    for(auto i : obj)
    {
        if(i.isString())
        {
            std::get<DataType::String>(jsonData)[keys[indexKey]] = i.toString();
        }
        else if(i.isDouble())
        {
            std::get<DataType::Double>(jsonData)[keys[indexKey]] = i.toDouble();
        }
        else if(i.isBool())
        {
            std::get<DataType::Bool>(jsonData)[keys[indexKey]] = i.toBool();
        }
        ++indexKey;
    }
    return std::move(jsonData);
}

QJsonObject MainWindow::makeJsonFont() const
{
    QFont fontText = ui->memo->font();
    QFontInfo info(fontText);

    QJsonObject dataFont
        {
        {"Family", info.family()},
        {"Style", mStyleName},
        {"Size", info.pointSize()}
    };
    return dataFont;
}

QJsonObject MainWindow::makeJsonWordWrap() const
{
    return QJsonObject { {"checked", ui->actionWord_Wrap->isChecked()} };
}

QJsonObject MainWindow::makeJsonStatusBar() const
{
    return QJsonObject { {"checked", ui->actionStatus_Bar->isChecked()} };
}

QJsonObject MainWindow::makeJsonPath() const
{
     return QJsonObject { {"dir", mFile.fileName()} };
}

QJsonObject MainWindow::makeGenerealJsonObject()
{
    return QJsonObject{
        {"Font", QJsonValue(makeJsonFont())},
        {"Word Wrap", QJsonValue(makeJsonWordWrap())},
        {"Status Bar", QJsonValue(makeJsonStatusBar())},
        {"Opened directory", QJsonValue(makeJsonPath())}
    };
}

void MainWindow::writeJsonConfig(QFile &config)
{
    config.open(QIODevice::WriteOnly);
    config.resize(0);

    QJsonDocument doc(makeGenerealJsonObject());

    auto byteData = doc.toJson();

    QTextStream writeStream(&config);

    writeStream << byteData;

    config.close();
}

void MainWindow::readConfigFrom(const QString &path, const QString &file)
{
    QDir dir = qApp->applicationDirPath();
    QFile config(dir.absolutePath().append("/%1/%2").arg(path).arg(file));
    qDebug() << config.fileName();

    QJsonDocument doc;

    config.open(QIODevice::ReadOnly);
    QByteArray byteData = config.readAll();

    QJsonParseError errorParser;
    auto readedDoc = doc.fromJson(byteData, &errorParser);
    auto obj = readedDoc.object();
    qDebug() << "coutn: " << obj.count();
    if(errorParser.error != QJsonParseError::NoError)
    {
        config.close();
        config.open(QIODevice::WriteOnly);
        config.resize(0);
        config.close();
        QFont defFont;
    }
    else
    {
        int indexKey = 0;
        QStringList keys = obj.keys();
        for(auto i : obj)
        {
            qDebug() << "key: " << keys[indexKey];
            if(i.isObject())
            {
                if(keys[indexKey] == "Word Wrap")
                {
                    ui->actionWord_Wrap->setChecked(readWordWrap(i.toObject()));
                }
                else if(keys[indexKey] == "Status Bar")
                {
                    ui->actionStatus_Bar->setChecked(readStatusBar(i.toObject()));
                }
                else if(keys[indexKey] == "Font")
                {
                    ui->memo->setFont(readFont(i.toObject()));
                }
                else if(keys[indexKey] == "Opened directory")
                {
                    lastDir = readPath(i.toObject());
                }
            }
            ++indexKey;
        }
    }
}
