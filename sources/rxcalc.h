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
#include "rxtable.h"

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
#include <QSettings>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QDesktopServices>
#include <QFileDialog>

class RxCalcApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit RxCalcApp();
    ~RxCalcApp();

private:
    RxTable *table;
    QDoubleSpinBox *inputPower_dBm, *noiseBand_Hz, *minSignalToNoise_dB, *temperature_K_C, *perToRms_dB;
    QLineEdit *gain_dB, *noiseFigure_dB, *inputIP3_dBm, *outputIP3_dBm, *inputP1dB_dBm, *outputP1dB_dBm, *outpupPower_dBm;
    QLineEdit *noiseFloor_dBmHz, *outputNSD_dBmHz, *outputNoiseFloor_dBm, *snr_dB, *mds_dBm, *sensivity_dBm, *noiseTemperature_K;
    QLineEdit *outpuiIMlevel_dBm, *outpuiIMlevel_dBc, *inpuiIMlevel_dBm, *inpuiIMlevel_dBc, *imd_dB, *sfdr_dB, *ildr_dB;
    QComboBox *temperatureUnit, *freqUnit;
    QPushButton *calcButton;
    QSpinBox *numberOfStages;
    QPlainTextEdit *comment;
    QString defaultPath;
    QString openProjectPath;
    System *system;
    enum temperatureUnits {
        celsius,
        kelvin
    };
    enum freqUnits {
        Hz,
        kHz,
        MHz,
        GHz
    };

signals:

protected:
    void closeEvent(QCloseEvent*);

public slots:
    void saveSettings();
    void loadSettings();
    void slotNew();
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotHelp();
    void slotAbout();
    void validateTemperature();
    void setStagesNumberSlot();
    void setStagesNumber(int number);

private slots:
    void clickOnCalcButton();
    void openProjectFile(QString fileName);
    void saveProjectAs(QString fileName);
    QString rounding(float input);
};

#endif // RXCALC_H
