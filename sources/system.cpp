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

#include "system.h"

System::System(): QObject()
{
    stageList  = new QList<Stage *> ();

    setInputPower(-60);
    setNoiseBand(1000);
    setMinSignalToNoise(10);
    setTemperature_C(25);
    setPeakToRatio(0);


    // System params:
    sys1.sysPowerGain = NAN;
    sys1.sysNoiseFigure = NAN;
    sys1.sysIip3 = NAN;
    sys1.sysOip3 = NAN;
    sys1.sysIp1db = NAN;
    sys1.sysOp1db = NAN;
    sys1.sysOutputPower = NAN;
    sys1.sysNoiseFloor_dbmHz = NAN;
    sys1.sysOutputNsd_dbmHz = NAN;
    sys1.sysNoiseFloor_dbm = NAN;
    sys1.snr = NAN;
    sys1.mds = NAN;
    sys1.noiseTemperature = NAN;
    sys1.sensivity = NAN;
    sys1.inputImLevel_dBm = NAN;
    sys1.outputImLevel_dBm = NAN;
    sys1.inputImLevel_dBc = NAN;
    sys1.outputImLevel_dBc = NAN;
    sys1.imd = NAN;
    sys1.sfdr = NAN;
}

System::~System()
{

}

void System::setInputPower(double inputPower)
{
    m_inputPower = inputPower;
}

double System::inputPower()
{
    return m_inputPower;
}

void System::setNoiseBand(float noiseBand)
{
    m_noiseBand = noiseBand;
}

float System::noiseBand()
{
    return m_noiseBand;
}

void System::setMinSignalToNoise(double minSignalToNoise)
{
    m_minSignalToNoise = minSignalToNoise;
}

double System::minSignalToNoise()
{
    return m_minSignalToNoise;
}

void System::setTemperature_K(float temperature)
{
    m_temperature_K = temperature;
    m_temperature_C = temperature + ABS_ZERO;
    m_useCelsium = kelvin;
}

float System::temperature_K()
{
    return m_temperature_K;
}

void System::setTemperature_C(float temperature)
{
    m_temperature_C = temperature;
    m_temperature_K = temperature - ABS_ZERO;
    m_useCelsium = celsius;
}

float System::temperature_C()
{
    return m_temperature_C;
}

void System::setPeakToRatio(double peakToRatio)
{
    m_peakToRatio = peakToRatio;
}

double System::peakToRatio()
{
    return m_peakToRatio;
}

void System::setUseCelsium(System::temperatureUnits val)
{
    m_useCelsium = val;
}

System::temperatureUnits System::useCelsium()
{
    return m_useCelsium;
}

void System::solve()
{
    solveSysPowerGain(); //first
    solveSysNoiseFigure(); // second
    solveSysIp3(); //third
    solveSysOutputPower();//fourth
    solveSysP1db();//fifth
    solveSysNoiseParam();//sixth
    solveDynamicParam(); //saeventh

    sys1.sysPowerGain = m_sysPowerGain;
    sys1.sysNoiseFigure = m_sysNoiseFigure;
    sys1.sysIip3 = m_sysIip3;
    sys1.sysOip3 = m_sysOip3;
    sys1.sysIp1db = m_sysIp1db;
    sys1.sysOp1db = m_sysOp1db;
    sys1.sysOutputPower = m_sysOutputPower;
    sys1.sysNoiseFloor_dbmHz = m_sysNoiseFloor_dbmHz;
    sys1.sysOutputNsd_dbmHz = m_sysOutputNsd_dbmHz;
    sys1.sysNoiseFloor_dbm = m_sysNoiseFloor_dbm;
    sys1.snr = m_snr;
    sys1.mds = m_mds;
    sys1.noiseTemperature = m_noiseTemperature;
    sys1.sensivity = m_sensivity;
    sys1.inputImLevel_dBm = m_inputImLevel_dBm;
    sys1.outputImLevel_dBm = m_outputImLevel_dBm;
    sys1.inputImLevel_dBc = m_inputImLevel_dBc;
    sys1.outputImLevel_dBc = m_outputImLevel_dBc;
    sys1.imd = m_imd;
    sys1.sfdr = m_sfdr;

    postSolveParam(); //eighth
}

float System::converdBtoKp(float dB)
{
    return pow(10.0, dB / (10.0));
}

float System::converdBtoW(float W)
{
    return  pow(10.0, W / (10.0)) / 1000.0;
}

float System::converKptodB(float Kp)
{
    return 10.0 * log10(Kp);
}

void System::solveSysPowerGain()
{
    // sysPowerGain = gain_1 + gain_2 + ... + gain_N

    m_sysPowerGain = 0;

    for (int i = 0; i < stageList->count(); i++)
    {
        if (stageList->at(i)->enabled() == false)
        {
            stageList->at(i)->sys.powerGain = NAN; // add data in paramList
            continue;
        }

        m_sysPowerGain += stageList->at(i)->powerGain();
        stageList->at(i)->sys.powerGain = m_sysPowerGain; // add data in paramList
    }
}

void System::solveSysNoiseFigure()
{
    // sysNoiseFigure = nf_1 + (nf_2-1)/gain_1 + (nf_3-1)/(gain_1*gain_2) + ... + (nf_N-1)/(gain_1*gain_2* ... *gain_N-1)

    bool firstStage = true;
    float tmp_gain = 0;
    m_sysNoiseFigure = 0;

    for (int i = 0; i < stageList->count(); i++)
    {
        if (stageList->at(i)->enabled() == false)
        {
            stageList->at(i)->sys.noiseFigure = NAN; // add data in paramList
            continue;
        }

        if (firstStage == true)
        {
            // only first stage
            m_sysNoiseFigure = converdBtoKp(stageList->at(i)->noiseFigure());
            firstStage = false;
        }
        else
        {
            // other stages
            m_sysNoiseFigure += (converdBtoKp(stageList->at(i)->noiseFigure()) - 1) / converdBtoKp(tmp_gain);
        }

        tmp_gain += stageList->at(i)->powerGain();
        stageList->at(i)->sys.noiseFigure = converKptodB(m_sysNoiseFigure); // add data in paramList
    }
    m_sysNoiseFigure = converKptodB(m_sysNoiseFigure);
}


void System::solveSysIp3()
{
    // m_sysOip3 = 1/((1/(ip3_N-1*Gain_N)) + (1/ip3N))
    // m_sysIip3 = m_sysOip3 - sysGain;

    bool firstStage = true;
    m_sysOip3 = 0;

    for (int i = 0; i < stageList->count(); i++)
    {
        if (stageList->at(i)->enabled() == false)
        {
            stageList->at(i)->sys.iip3 = NAN; // add data in paramList
            stageList->at(i)->sys.oip3 = NAN; // add data in paramList
            continue;
        }

        if (firstStage == true)
        {
            // only first stage
            m_sysOip3 = converdBtoKp(stageList->at(i)->oip3());
            firstStage = false;
        }
        else
        {
            // other stages
            m_sysOip3 = 1 / ((1 / (m_sysOip3 * converdBtoKp(stageList->at(i)->powerGain()))) + (1 / converdBtoKp(stageList->at(i)->oip3())));
        }

        stageList->at(i)->sys.oip3 = converKptodB(m_sysOip3); // add data in paramList
        stageList->at(i)->sys.iip3 =  stageList->at(i)->sys.oip3 -  stageList->at(i)->sys.powerGain; // add data in paramList
    }
    m_sysOip3 = converKptodB(m_sysOip3);
    m_sysIip3 = m_sysOip3 - m_sysPowerGain;
}

void System::solveSysP1db()
{
    // m_sysOp1db = 1/((1/(ip1_N-1*Gain_N)) + (1/ip1_N))
    // m_sysIp1db = m_sysOp1db - (sysGain - 1);

    bool firstStage = true;
    m_sysOp1db = 0;

    for (int i = 0; i < stageList->count(); i++)
    {
        if (stageList->at(i)->enabled() == false)
        {
            stageList->at(i)->sys.powerOutBackoff = NAN; // add data in paramList
            stageList->at(i)->sys.peakPowerOutBackoff = NAN; // add data in paramList
            continue;
        }

        if (firstStage == true)
        {
            // only first stage
            m_sysOp1db = converdBtoKp(stageList->at(i)->op1db());
            firstStage = false;
        }
        else
        {
            // other stages
            m_sysOp1db = 1 / ((1 / (m_sysOp1db * converdBtoKp(stageList->at(i)->powerGain()))) + (1 / converdBtoKp(stageList->at(i)->op1db())));
        }
        stageList->at(i)->sys.op1db = converKptodB(m_sysOp1db);
        stageList->at(i)->sys.ip1db = stageList->at(i)->sys.op1db - (stageList->at(i)->sys.powerGain - 1);

        stageList->at(i)->sys.powerOutBackoff = stageList->at(i)->op1db() - stageList->at(i)->sys.outputPower; // add data in paramList
        stageList->at(i)->sys.peakPowerOutBackoff = stageList->at(i)->sys.powerOutBackoff - m_peakToRatio; // add data in paramList
    }
    m_sysOp1db = converKptodB(m_sysOp1db);
    m_sysIp1db = m_sysOp1db - (m_sysPowerGain - 1);
}

void System::solveSysOutputPower()
{
    bool firstStage = true;
    float tmp_OutputPower = 0;

    for (int i = 0; i < stageList->count(); i++)
    {
        if (stageList->at(i)->enabled() == false)
        {
            stageList->at(i)->sys.inputPower = NAN; // add data in paramList
            stageList->at(i)->sys.outputPower = NAN; // add data in paramList
            continue;
        }

        if (firstStage == true)
        {
            // only first stage
            stageList->at(i)->sys.inputPower = m_inputPower; // add data in paramList
            firstStage = false;
        }
        else
        {
            // other stages
            stageList->at(i)->sys.inputPower = tmp_OutputPower;
        }
        tmp_OutputPower = stageList->at(i)->sys.inputPower + stageList->at(i)->powerGain(); // add data in paramList
        stageList->at(i)->sys.outputPower = tmp_OutputPower;
    }
    m_sysOutputPower = m_inputPower + m_sysPowerGain;
}

void System::solveSysNoiseParam()
{
    float pinNoiseHz_dbm = 10.0 * (log10(1.3806488 * m_temperature_K) - 23.0 + 3.0); // = k*T (where k = 1.3806488*10^-23, +3.0-milliwatt)
    float pinnoise = pinNoiseHz_dbm + 10.0 * log10(m_noiseBand);
    float poutNoise = m_sysPowerGain + m_sysNoiseFigure + pinnoise;

    m_sysNoiseFloor_dbmHz = pinNoiseHz_dbm + m_sysNoiseFigure ;
    m_sysOutputNsd_dbmHz = m_sysNoiseFloor_dbmHz + m_sysPowerGain;
    m_sysNoiseFloor_dbm = poutNoise;
    m_snr = m_sysOutputPower - poutNoise;
    m_mds = pinnoise + m_sysNoiseFigure;
    m_noiseTemperature = m_temperature_K * (converdBtoKp(m_sysNoiseFigure) - 1);
    m_sensivity = pinnoise + m_sysNoiseFigure + m_minSignalToNoise;
}

void System::solveDynamicParam()
{
    float outpIMLevel = m_sysOutputPower - 2 * (m_sysOip3 - m_sysOutputPower);
    float inIMLevel = m_inputPower - 2 * ((m_sysOip3 - m_sysPowerGain) - m_inputPower);

    m_inputImLevel_dBm = inIMLevel;
    m_outputImLevel_dBm = outpIMLevel;
    m_outputImLevel_dBc = outpIMLevel - m_sysOutputPower;
    m_inputImLevel_dBc = inIMLevel - m_inputPower;
    m_imd = 2 * ((m_sysOutputPower - 3.0) - m_sysOip3);
    m_sfdr = (2.0 / 3.0) * (m_sysOip3 - m_sysNoiseFloor_dbm);
}

#include <cfloat>

void System::postSolveParam()
{
    bool firstStage = true;
    float oldNF = 0;
    float oldIIP = 0;
    float oldOIP = 0;

    for (int i = 0; i < stageList->count(); i++)
    {
        if (stageList->at(i)->enabled() == false)
        {
            stageList->at(i)->sys.stageIip3ToSystemIip3 = NAN; // add data in paramList
            stageList->at(i)->sys.noiseFigureToSystemNoiseFigure = NAN; // add data in paramList
            stageList->at(i)->sys.oip3StageToOp3System = NAN; // add data in paramList
            continue;
        }

        if (firstStage == true)
        {
            // only first stage
            stageList->at(i)->sys.noiseFigureToSystemNoiseFigure = stageList->at(i)->sys.noiseFigure / m_sysNoiseFigure; // add data in paramList
            stageList->at(i)->sys.stageIip3ToSystemIip3 = (1.0 / converdBtoW(stageList->at(i)->sys.iip3)) / (1.0 / converdBtoW(m_sysIip3));
            stageList->at(i)->sys.oip3StageToOp3System = (1.0 / converdBtoW(stageList->at(i)->sys.oip3)) / (1.0 / converdBtoW(m_sysOip3));
            firstStage = false;
        }
        else
        {
            // other stages
            stageList->at(i)->sys.noiseFigureToSystemNoiseFigure = (stageList->at(i)->sys.noiseFigure - oldNF) / m_sysNoiseFigure;
            stageList->at(i)->sys.stageIip3ToSystemIip3 = ((1.0 / converdBtoW(stageList->at(i)->sys.iip3)) - (1.0 / converdBtoW(oldIIP))) / (1.0 / converdBtoW(m_sysIip3));
            stageList->at(i)->sys.oip3StageToOp3System = ((1.0 / converdBtoW(stageList->at(i)->sys.oip3)) - (1.0 / converdBtoW(oldOIP))) / (1.0 / converdBtoW(m_sysOip3));
        }
        oldNF = stageList->at(i)->sys.noiseFigure;
        oldOIP = stageList->at(i)->sys.oip3;
        oldIIP = stageList->at(i)->sys.iip3;
    }

}
