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
    setName("Name");
    setEnabled(true);
    setPowerGain(0);
    setNoiseFigure(0);
    setIip3(0);
    setIp1db(0);
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

    if (iip3Priority == true)
        m_oip3 = m_iip3 + m_powerGain;
    else
        m_iip3 = m_oip3 - m_powerGain;

    if (ip1dbPriority == true)
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
    iip3Priority = false;
}

float Stage::oip3()
{
    return m_oip3;
}

void Stage::setOp1db(float op1db)
{
    m_op1db = op1db;
    m_ip1db = m_op1db - (m_powerGain - 1);
    ip1dbPriority = false;
}

float Stage::op1db()
{
    return m_op1db;
}

void Stage::setIip3(float iip3)
{
    m_iip3 = iip3;
    m_oip3 = m_iip3 + m_powerGain;
    iip3Priority = true;
}

float Stage::iip3()
{
    return m_iip3;
}

void Stage::setIp1db(float ip1db)
{
    m_ip1db = ip1db;
    m_op1db = m_ip1db + (m_powerGain - 1);
    ip1dbPriority = true;
}

float Stage::ip1db()
{
    return m_ip1db;
}

