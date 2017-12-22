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

#ifndef SYSTEM_H
#define SYSTEM_H

#define ABS_ZERO (-273.15)

#include "stage.h"

#include <QList>
#include <QObject>

class System : public QObject
{
    Q_OBJECT

public:
    System();
    ~System();
    QList<Stage *> *stageList;
    // System params:
    typedef struct
    {
        float sysPowerGain;
        float sysNoiseFigure;
        float sysIip3;
        float sysOip3;
        float sysIp1db;
        float sysOp1db;
        float sysOutputPower;
        float sysNoiseFloor_dbmHz;
        float sysOutputNsd_dbmHz;
        float sysNoiseFloor_dbm;
        float snr;
        float mds;
        float noiseTemperature;
        float sensivity;
        float inputImLevel_dBm;
        float outputImLevel_dBm;
        float inputImLevel_dBc;
        float outputImLevel_dBc;
        float imd;
        float sfdr;
    } sysStruct;
    sysStruct sys1;
    enum temperatureUnits
    {
        celsius,
        kelvin
    };

public slots:
    void setInputPower(double inputPower);
    double inputPower();
    void setNoiseBand(float noiseBand);
    float noiseBand();
    void setMinSignalToNoise(double minSignalToNoise);
    double minSignalToNoise();
    void setTemperature_K(float temperature_K);
    float temperature_K();
    void setTemperature_C(float temperature_C);
    float temperature_C();
    void setPeakToRatio(double peakToRatio);
    double peakToRatio();
    void solve();
    void setUseCelsium(temperatureUnits val);
    temperatureUnits useCelsium();

private slots:
    float converdBtoKp(float dB);
    float converdBtoW(float W);
    float converKptodB(float Kp);
    void solveSysPowerGain();
    void solveSysNoiseFigure();
    void solveSysIp3();
    void solveSysOutputPower();
    void solveSysP1db();
    void solveSysNoiseParam();
    void solveDynamicParam();
    void postSolveParam();

private:
    //Input param
    double m_inputPower;
    float m_noiseBand;
    double m_minSignalToNoise;
    float m_temperature_K;
    float m_temperature_C;
    double m_peakToRatio;
    //Output param
    float m_sysPowerGain;
    float m_sysNoiseFigure;
    float m_sysIip3;
    float m_sysOip3;
    float m_sysIp1db;
    float m_sysOp1db;
    float m_sysOutputPower;
    float m_sysNoiseFloor_dbmHz;
    float m_sysOutputNsd_dbmHz;
    float m_sysNoiseFloor_dbm;
    float m_snr;
    float m_mds;
    float m_noiseTemperature;
    float m_sensivity;
    float m_inputImLevel_dBm;
    float m_outputImLevel_dBm;
    float m_inputImLevel_dBc;
    float m_outputImLevel_dBc;
    float m_imd;
    float m_sfdr;
    temperatureUnits m_useCelsium;
};

#endif // SYSTEM_H
