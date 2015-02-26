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

class System
{
public:
    System(QList<Stage*> *stageList);
    ~System();
    void setInputPower(float inputPower);
    float inputPower();
    void setNoiseBand(float noiseBand);
    float noiseBand();
    void setMinSignalToNoise(float minSignalToNoise);
    float minSignalToNoise();
    void setTemperature_K(float temperature_K);
    float temperature_K();
    void setTemperature_C(float temperature_C);
    float temperature_C();
    void setPeakToRatio(float peakToRatio);
    float peakToRatio();
    void solve();
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
        float inputImLevel;
        float outputImLevel;
        float imLevel_dbc;
        float imd;
        float sfdr;
    } sysStruct;
    sysStruct sys1;

private:
    float converdBtoKp(float dB);
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
    QList<Stage*> *m_stageList;
    //Input param
    float m_inputPower;
    float m_noiseBand;
    float m_minSignalToNoise;
    float m_temperature_K;
    float m_temperature_C;
    float m_peakToRatio;
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
    float m_inputImLevel;
    float m_outputImLevel;
    float m_imLevel_dbc;
    float m_imd;
    float m_sfdr;
};

#endif // SYSTEM_H
