//Copyright (C) 2017  Baranov Mykola

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see http://www.gnu.org/licenses/

//// \brief MainWindow. Responds for all basic features, signals and slots.

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

    ui->memo->setFont(readConfig(ConfigPath, ConfigNameFile));
}

MainWindow::~MainWindow()
{
    saveFontTo(ConfigPath, ConfigNameFile);
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

void MainWindow::slotOpenFile()
{
    stateSave->open(*this);
}

void MainWindow::slotNewFile()
{
    stateSave->newDoc(*this);
}

void MainWindow::slotSaveFile()
{
    stateSave->save(*this);
}

void MainWindow::slotSaveAs()
{
    mFile.setFileName(saveAs());
    auto data = getPlainText();
    saveFileFunction(mFile, data);
    ui->statusBar->showMessage(QString("File saved as %1").arg(mFile.fileName()));
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

void MainWindow::saveFontTo(const QString &path, const QString& file)
{
    QDir dir = qApp->applicationDirPath();;
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
    config.open(QIODevice::WriteOnly);
    config.resize(0);

    QJsonObject dataFont = makeJsonFont();

    QJsonDocument doc(dataFont);

    auto byteData = doc.toJson();

    QTextStream writeStream(&config);

    writeStream << byteData;

    config.close();
}

void MainWindow::open()
{
    QFileDialog files;
    mPathFile = QFileDialog::getOpenFileName(this, tr("Open File..."), QDir::homePath(), "Text Files (*.txt);; All Files (*.*)");
    if(!mPathFile.isEmpty())
    {
        mFile.setFileName(mPathFile);
        if(mFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&mFile);
            QString data = stream.readAll();
            ui->memo->setPlainText(data);
            updateTitle(mPathFile);
            ui->statusBar->showMessage(tr("Opened file %1").arg(mFile.fileName()));
        }
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

QFont MainWindow::readConfig(const QString &path, const QString &file)
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
        return defFont.defaultFamily();
    }
    else
    {
        int size;
        std::map<QString, QString> fontProperties;
        int indexKey = 0;
        for(auto i : obj)
        {
            QStringList keys = obj.keys();
            if(i.isString())
            {
                fontProperties[keys[indexKey]] = i.toString();
                qDebug() << keys[indexKey] <<  i.toString() << indexKey;
            }
            else if(i.isDouble())
            {
                size = static_cast<int>(i.toDouble());
                qDebug() << size;
            }
            ++indexKey;
        }
        QFontDatabase base;
        mStyleName = fontProperties["Style"];
        return base.font(fontProperties["Family"], fontProperties["Style"], size);
    }
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

QJsonObject MainWindow::makeJsonWordWrap()
{
    return QJsonObject { {"Word Wrap", ui->actionWord_Wrap->isChecked()} };
}
