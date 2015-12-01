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

#include "stage.h"

Stage::Stage()
{
    // Stage params:
    setName("Name");
    setEnabled(true);
    setPowerGain(0);
    setNoiseFigure(0);
    setIip3(0);
    setIp1db(0);
    m_iip3Priority = undifinited;
    m_ip1dbPriority = undifinited;
    // System params:
    sys.powerGain=NAN;
    sys.noiseFigure=NAN;
    sys.iip3=NAN;
    sys.oip3=NAN;
    sys.ip1db=NAN;
    sys.op1db=NAN;
    sys.inputPower=NAN;
    sys.outputPower=NAN;
    sys.noiseFigureToSystemNoiseFigure=NAN;
    sys.stageIip3ToSystemIip3=NAN;
    sys.powerOutBackoff=NAN;
    sys.peakPowerOutBackoff=NAN;
}

Stage::~Stage()
{

}

void Stage::setName(QString name)
{
    m_name = name;
}

QString Stage::name()
{
    return m_name;
}

void Stage::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool Stage::enabled()
{
    return m_enabled;
}

void Stage::setPowerGain(float gain)
{
    m_powerGain = gain;

    if (m_iip3Priority == input)
        m_oip3 = m_iip3 + m_powerGain;
    else
        m_iip3 = m_oip3 - m_powerGain;

    if (m_ip1dbPriority == input)
        m_op1db = m_ip1db + (m_powerGain - 1);
    else
        m_ip1db = m_op1db - (m_powerGain - 1);
}

float Stage::powerGain()
{
    return m_powerGain;
}

void Stage::setNoiseFigure(float noise)
{
    m_noiseFigure = noise;
}

float Stage::noiseFigure()
{
    return m_noiseFigure;
}

void Stage::setOip3(float oip3)
{
    m_oip3 = oip3;
    m_iip3 = m_oip3 - m_powerGain;
    m_iip3Priority = output;
}

float Stage::oip3()
{
    return m_oip3;
}

void Stage::setOp1db(float op1db)
{
    m_op1db = op1db;
    m_ip1db = m_op1db - (m_powerGain - 1);
    m_ip1dbPriority = output;
}

float Stage::op1db()
{
    return m_op1db;
}

void Stage::setIip3(float iip3)
{
    m_iip3 = iip3;
    m_oip3 = m_iip3 + m_powerGain;
    m_iip3Priority = input;
}

float Stage::iip3()
{
    return m_iip3;
}

void Stage::setIp1db(float ip1db)
{
    m_ip1db = ip1db;
    m_op1db = m_ip1db + (m_powerGain - 1);
    m_ip1dbPriority = input;
}

float Stage::ip1db()
{
    return m_ip1db;
}

Stage::priority Stage::iip3Priority()
{
    return m_iip3Priority;
}

Stage::priority Stage::ip1dbPriority()
{
    return m_ip1dbPriority;
}
