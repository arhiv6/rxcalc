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
    System();
    ~System();
    QList<Stage*> *m_stageList;
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

private:
    float m_inputPower;
    float m_noiseBand;
    float m_minSignalToNoise;
    float m_temperature_K;
    float m_temperature_C;
    float m_peakToRatio;
};

#endif // SYSTEM_H
