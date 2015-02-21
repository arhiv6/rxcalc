/*
 * Copyright 2014, 2015 Verkhovin Vyacheslav
 *
 * This file is part of RxCalc.
 *
 * RxCalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RxCalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RxCalc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RXCALC_H
#define RXCALC_H

#include "stage.h"
#include "system.h"

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
#include <QSettings>

class RxCalcApp : public QMainWindow
{
    Q_OBJECT
public:
    explicit RxCalcApp();
    ~RxCalcApp();
    QTableWidget *table;

signals:

protected:
    void closeEvent(QCloseEvent*);

public slots:
    void saveSettings();
    void loadSettings();
};

#endif // RXCALC_H
