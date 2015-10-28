// $Id: SudokuApp.h 298M 2010-10-29 18:45:34Z (local) $


/**
 * SudokuApp definition.
 *
 * The sole reason for this class' existence is that we need the ability to
 * detect the ApplicationDeactivate event. (When this event occurs, we want
 * the game to be paused.)
 *
 * @file SudokuApp.h
 * @author Wim Leers
 */


#pragma once
#ifndef SUDOKUAPP_H
#define SUDOKUAPP_H


#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QDebug>
#include "Qt/MainWindow.h"


class SudokuApp : public QApplication
{
public:
    SudokuApp(int & argc, char ** argv);

protected:
    bool event(QEvent * event);

private:
    MainWindow * m_mainWindow;
};

#endif // SUDOKUAPP_H
