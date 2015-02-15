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

System::System()
{
    m_stageList = new QList<Stage*>;
}

System::~System()
{

}

void System::setInputPower(float inputPower)
{
    m_inputPower = inputPower;
}

float System::inputPower()
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

void System::setMinSignalToNoise(float minSignalToNoise)
{
    m_minSignalToNoise = minSignalToNoise;
}

float System::minSignalToNoise()
{
    return m_minSignalToNoise;
}

void System::setTemperature_K(float temperature)
{
    m_temperature_K = temperature;
    m_temperature_C = temperature + ABS_ZERO;
}

float System::temperature_K()
{
    return m_temperature_K;
}

void System::setTemperature_C(float temperature)
{
    m_temperature_C = temperature;
    m_temperature_K = temperature - ABS_ZERO;
}

float System::temperature_C()
{
    return m_temperature_C;
}

void System::setPeakToRatio(float peakToRatio)
{
    m_peakToRatio = peakToRatio;
}

float System::peakToRatio()
{
    return m_peakToRatio;
}
